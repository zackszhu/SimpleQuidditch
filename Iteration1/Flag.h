#pragma once
#include <vector>
#include "Vector.h"
const int FLAG_HEIGHT = 6;
const int FLAG_WIDTH = 6;


class Flag {
	std::vector<std::vector<Vec>> flagPoints;
	GLfloat points[FLAG_HEIGHT][FLAG_WIDTH][3];
	GLuint texture;

public:
	Flag();
	GLfloat* toGLFloat();
	GLuint getTexture() const;
	void rotateBias(double x);
	void move();
};
