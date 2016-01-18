#pragma once
#include "Vector.h"
#include "Point.h"

class Physics;
class Renderer;

class Tile {
	Point leftTop, rightTop, leftBottom, rightBottom;
	Vec normal, gradient;
	GLfloat ambient[3];
	GLfloat specular[3];
public:
	friend Renderer;
	friend Physics;
	Tile();
	Tile(const Point& lt, const Point& rt, const Point& rb, const Point& lb);
};
