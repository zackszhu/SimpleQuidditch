#define _USE_MATH_DEFINES
#include "Flag.h"
#include <cmath>
#include "GL/SOIL.h"

GLuint loadFlagImage() {
	GLuint tex_2d = SOIL_load_OGL_texture("imgs/quidditch.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (tex_2d == 0)
		return -1;
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return tex_2d;
}

Flag::Flag(): flagPoints(FLAG_HEIGHT, std::vector<Vec>(FLAG_WIDTH)) {
	for (auto i = 0; i < FLAG_HEIGHT; i++) {
		for (auto j = 0; j < FLAG_WIDTH; j++) {
			flagPoints[i][j] = Vec(-15 - j * 0.75, -5 + j * 0.75, 2.5 - i * 0.75);
		}
	}
	texture = loadFlagImage();
}

GLfloat* Flag::toGLFloat() {
	for (auto i = 0; i < FLAG_HEIGHT; i++) {
		for (auto j = 0; j < FLAG_WIDTH; j++) {
			points[i][j][0] = flagPoints[i][j].x;
			points[i][j][1] = flagPoints[i][j].y;
			points[i][j][2] = flagPoints[i][j].z;
		}
	}
	return &points[0][0][0];
}

GLuint Flag::getTexture() const {
	return texture;
}

void Flag::rotateBias(double x) {
	auto theta = x / 180 * M_PI;
//	for (auto i = 0; i < FLAG_HEIGHT; i++) {
//		for (auto j = 0; j < FLAG_WIDTH; j++) {
//			auto tmpx = flagPoints[i][j].x * cos(theta) + flagPoints[i][j].y * sin(theta);
//			flagPoints[i][j].y = -flagPoints[i][j].x * sin(theta) + flagPoints[i][j].y * cos(theta);
//			flagPoints[i][j].x = tmpx;
//		}
//	}
	auto tmpx = flagPoints[0][0].x * cos(theta) + flagPoints[0][0].y * sin(theta);
	flagPoints[0][0].y = -flagPoints[0][0].x * sin(theta) + flagPoints[0][0].y * cos(theta);
	flagPoints[0][0].x = tmpx;
	tmpx = flagPoints[0][FLAG_WIDTH - 1].x * cos(theta) + flagPoints[0][FLAG_WIDTH - 1].y * sin(theta);
	flagPoints[0][FLAG_WIDTH - 1].y = -flagPoints[0][FLAG_WIDTH - 1].x * sin(theta) + flagPoints[0][FLAG_WIDTH - 1].y * cos(theta);
	flagPoints[0][FLAG_WIDTH - 1].x = tmpx;
}

void Flag::move() {
	GLfloat cgravity = 0.075;
	GLfloat c = 0.125;
	std::vector<std::vector<Vec>> points2(FLAG_HEIGHT, std::vector<Vec>(FLAG_WIDTH));
	GLfloat normalPoint[4] = { 1.0, 1.414, 2.336, 2.828 };
	for (auto i = 0; i < FLAG_HEIGHT; i++) {
		for (auto j = 0; j < FLAG_WIDTH; j++) {
			Vec movement = Vec(0, 0, -cgravity);
			for (auto di = -2; di < 3; di++) {
				for (auto dj = -2; dj < 3; dj++) {
					if (di == 0 && dj == 0)
						continue;
					auto ii = i + di, jj = j + dj;
					if (ii < 0 || ii > FLAG_HEIGHT - 1 || jj < 0 || jj > FLAG_WIDTH - 1)
						continue;
					auto spring = flagPoints[ii][jj] - flagPoints[i][j];
					auto length = spring.length();
					auto normal = normalPoint[abs(di) + abs(dj) - 1] * 0.75;
					auto scaler = (length - normal) / normal;
					spring = length == 0 ? Vec() : (spring / length);
					auto force = scaler * c * spring ;
					movement = force + movement;
				}
			}
			points2[i][j] = flagPoints[i][j] + movement;
		}
	}
	for (auto i = 0; i < FLAG_HEIGHT; i++) {
		for (auto j = 0; j < FLAG_WIDTH; j++) {
			if (i == 0 && j == 0 || i == 0 && j == FLAG_WIDTH - 1)
				continue;
			flagPoints[i][j] = points2[i][j];
		}
	}
}
