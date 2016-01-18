#include "Point.h"
#include <utility>

Point::Point()
	:x(0.0),
	y(0.0),
	z(0.0) {}

Point::Point(GLfloat x, GLfloat y, GLfloat z)
	: x(x),
	y(y),
	z(z) {}

Point::Point(const Point& other)
	: x(other.x),
	y(other.y),
	z(other.z) {}

Point::Point(Point&& other)
	: x(other.x),
	y(other.y),
	z(other.z) {}

Point& Point::operator=(const Point& other) {
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Point& Point::operator=(Point&& other) {
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Point operator+(const Point& pos, const Vec& vec) {
	return std::move(Point(pos.x + vec.x, pos.y + vec.y, pos.z + vec.z));
}

Point operator-(const Point& pos, const Vec& vec) {
	return std::move(Point(pos.x - vec.x, pos.y - vec.y, pos.z - vec.z));
}

Vec operator-(const Point& point_1, const Point& point_2) {
	return std::move(Vec(point_1.x - point_2.x, point_1.y - point_2.y, point_1.z - point_2.z));
}