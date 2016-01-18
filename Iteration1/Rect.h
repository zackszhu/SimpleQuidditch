#pragma once
#include <gl/glut.h>

class Rect {
public:
	GLfloat x, y, z, w, l, h;

	Rect();

	Rect(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat l, GLfloat h);

	Rect(const Rect& other);

	Rect(Rect&& other);

	Rect& operator=(const Rect& other);

	Rect& operator=(Rect&& other);
};
