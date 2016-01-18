#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include "Renderer.h"
#include "Text.h"
#include "Lighter.h"
#include "Flag.h"
#include "Desk.h"
#include "Ball.h"
#include "Wall.h"
#include "Emitter.h"
#include "Tile.h"

void Renderer::init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glShadeModel(GL_FLAT);

}

void Renderer::displayInit() {
	Lighter::init();
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Desk& desk) {
	glEnable(GL_LIGHTING);
	renderFill(desk);
	glDisable(GL_LIGHTING);
	renderOutline(desk);
}

void Renderer::render(const Text& text) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glColor3f(0, 0, 0);
	glRasterPos2f(text.pos.x, text.pos.y);
	for each (auto ch in text.content) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Renderer::renderOutline(const Desk& desk) {
	for each (auto rect in desk.rects) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		glTranslatef(rect.x, rect.y, rect.z);
		glScalef(rect.w, rect.l, rect.h);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1.0);
		glPopMatrix();
		glPopAttrib();
	}
}

void Renderer::renderFill(const Desk& desk) {
	for each (auto rect in desk.rects) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		glDisable(GL_LIGHT2);
		glTranslatef(rect.x, rect.y, rect.z);
		glScalef(rect.w, rect.l, rect.h);
		GLfloat ambient[3] = { 0.4, 0.4, 0.4 };
		GLfloat specular[3] = { 0.8, 0.8, 0.8 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glPolygonOffset(1.0, 1.0);
		glColor3f(1.0, 1.0, 1.0);
		glutSolidCube(1.0);
		glEnable(GL_LIGHT2);
		glPopMatrix();
		glPopAttrib();
	}
	for each (auto tileLine in desk.tiles) {
		for each (auto tile in tileLine) {
			render(tile);
		}
	}
}

void Renderer::render(Ball& ball) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
	glTranslatef(ball.pos.x, ball.pos.y, ball.pos.z + ballRadius);
	glEnable(GL_POLYGON_OFFSET_FILL);

	// Outline
	glDisable(GL_LIGHTING);
	glPolygonOffset(-3.0f, 3.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(ballRadius, 40, 40);
	// Fill
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (ball.texture > 0) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ball.texture);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glMatrixMode(GL_TEXTURE);
		glRotatef(-1 * ball.rotation * 4 * 3.1415926535, ball.normal.x, ball.normal.z, ball.normal.y);
		double matrix[16];
		glGetDoublev(GL_TEXTURE_MATRIX, matrix);
		glLightModelf(0x81F8, 0x81FA);
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT, ball.ballGui.ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ball.ballGui.specular);
	glutSolidSphere(ballRadius, 40, 40);
	glMatrixMode(GL_MODELVIEW);


	if (ball.texture > 0) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	glDisable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glPopMatrix();
	glPopAttrib();
}

void Renderer::render(const Point& point) {
	const auto edges = 100;
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glTranslatef(point.x, point.y, point.z);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (auto i = 0; i < edges; i++)
		glVertex2f(ballRadius * cos(2 * M_PI / edges * i), ballRadius * sin(2 * M_PI / edges * i));
	glEnd();
	glPopMatrix();
	glPopAttrib();
}

void Renderer::render(int score) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glColor3f(0, 0, 0);
	glRasterPos2f(-0.8, 0.7);
	std::string str{ "Score: " };
	std::stringstream scoreStr;
	scoreStr << score;
	for each (auto ch in str) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
	}
	for each (auto ch in scoreStr.str()) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

void Renderer::render(Flag& flag) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	GLfloat texpts[2][2][2] = { { { 0.0, 0.0 },{ 0.0, 1.0 } }, { { 1.0, 0.0 },{ 1.0, 1.0 } } };
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, FLAG_WIDTH, 0, 1, FLAG_WIDTH * 3, FLAG_HEIGHT, flag.toGLFloat());
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0][0][0]);
	glMapGrid2f(40, 0.0, 1.0, 40, 0.0, 1.0);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(-3.0f, -3.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glEvalMesh2(GL_FILL, 0, 40, 0, 40);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, flag.getTexture());
	glEvalMesh2(GL_FILL, 0, 40, 0, 40);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


	glPopMatrix();
	glPopAttrib();
}

void Renderer::render(const Wall& wall) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wall.getTexture());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(wall.leftBottom.x, wall.leftBottom.y, wall.leftBottom.z);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(wall.rightBottom.x, wall.rightBottom.y, wall.rightBottom.z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(wall.rightTop.x, wall.rightTop.y, wall.rightTop.z);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(wall.leftTop.x, wall.leftTop.y, wall.leftTop.z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();
	glPopAttrib();
}

void Renderer::render(const Emitter& emitter) {
	for (auto it = emitter.particles.begin(); it != emitter.particles.end(); ++it) {
		render(*it);
	}
}

void Renderer::render(const Particle& particle) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 0.0);
	glTranslated(particle.position.x, particle.position.y, particle.position.z);
	glutSolidSphere(0.02, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPopAttrib();
}

void Renderer::render(const Tile& tile) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT, tile.ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tile.specular);
	glVertex3f(tile.leftTop.x, tile.leftTop.y, tile.leftTop.z);
	glVertex3f(tile.rightTop.x, tile.rightTop.y, tile.rightTop.z);
	glVertex3f(tile.rightBottom.x, tile.rightBottom.y, tile.rightBottom.z);
	glVertex3f(tile.leftBottom.x, tile.leftBottom.y, tile.leftBottom.z);
	glEnd();
	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(tile.leftTop.x, tile.leftTop.y, tile.leftTop.z);
	glVertex3f(tile.rightTop.x, tile.rightTop.y, tile.rightTop.z);
	glVertex3f(tile.rightBottom.x, tile.rightBottom.y, tile.rightBottom.z);
	glVertex3f(tile.leftBottom.x, tile.leftBottom.y, tile.leftBottom.z);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPopAttrib();
}
