#pragma once
#include "gl\glut.h"
class BallGUI {
public:
	GLfloat ambient[3];
	GLfloat specular[3];

	BallGUI();
	BallGUI(GLfloat ambient[3], GLfloat specular[3]);
	BallGUI(const BallGUI& ballGui);
	~BallGUI();
};
