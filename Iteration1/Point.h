#pragma once
#include <GL/glut.h>
#include "Vector.h"

class Point {
public:
	friend Vec operator - (const Point& point_1, const Point & point_2);

	GLfloat x, y, z;

	Point();

	Point(GLfloat x, GLfloat y, GLfloat z);

	Point(const Point& other);

	Point(Point&& other);

	Point& operator=(const Point& other);

	Point& operator=(Point&& other);


};

Point operator + (const Point& pos, const Vec& vec);

Point operator - (const Point& pos, const Vec& vec);

