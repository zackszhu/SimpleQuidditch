#include "Lighter.h"
#include "Point.h"
#include "gl/glut.h"

bool Lighter::lightSwitch = true;

void Lighter::init() {

	GLfloat Light_Model_Ambient [] = { 0.2 , 0.2 , 0.2 , 1.0 }; //默认的全局环境光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient); //设置全局环境光的方法

	GLfloat lightPos_1 [] = { -5.0, 5.0, 5.0 , 0.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos_1);

	GLfloat lightPos_2 [] = { 0.0, 0.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos_2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
	GLfloat spot_direction [] = { 4.5 , 4.5 , -4.5 };
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);

	GLfloat whiteColor [] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat yellowColor [] = { 1.0, 1.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteColor);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT2, GL_AMBIENT, yellowColor);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, yellowColor);
	glLightfv(GL_LIGHT2, GL_SPECULAR, yellowColor);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
}

void Lighter::spotLightMove(const Point& pos) {
	if (!lightSwitch) {
		glDisable(GL_LIGHT2);
	}
	else {
		glEnable(GL_LIGHT2);
	}

	Point point1 = Point(0.0, 0.0, 5.0);
	Vec vec = pos - point1;
	GLfloat spot_direction [] = { vec.x , vec.y , vec.z };
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
}

void Lighter::spotLightSwitch() {
	lightSwitch = !lightSwitch;
}
