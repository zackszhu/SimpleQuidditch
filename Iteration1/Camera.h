#pragma once
#include <GL/glut.h>

class Camera {
	static float viewRotation;
public:
	static void setProject(GLfloat width, GLfloat height);
	static void setModel();
	static void rotate(GLfloat radius);
};
