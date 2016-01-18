#pragma once
#include <GL/glut.h>
#include "Vector.h"
#include <string>

class Wall {
	GLuint texture;
public:
	Vec leftTop, rightTop, leftBottom, rightBottom;

	GLuint getTexture() const;

	Wall();

	Wall(const Vec& left_bottom, const Vec& right_bottom, const Vec& right_top, const Vec& left_top, std::string filename);
};
