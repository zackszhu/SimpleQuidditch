#include "Vector.h"
#include <utility>
#include <cmath>

Vec::Vec() :x(0.0), y(0.0), z(0.0) {}

Vec::Vec(GLfloat x, GLfloat y, GLfloat z)
	: x(x),
	y(y),
	z(z) {}

Vec::Vec(const Vec& other)
	: x(other.x),
	y(other.y),
	z(other.z) {}

Vec::Vec(Vec&& other)
	: x(other.x),
	y(other.y),
	z(other.z) {}

Vec& Vec::operator=(const Vec& other) {
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vec& Vec::operator=(Vec&& other) {
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

GLfloat Vec::length() {
	return sqrt(x * x + y * y + z * z);
}

Vec Vec::random(GLfloat max, int integer) {
	auto tmp_1 = static_cast<int>(2 * max * integer);
	auto tmp_2 = static_cast<GLfloat>(integer);
	return Vec(rand() % tmp_1 / tmp_2 - max, rand() % tmp_1 / tmp_2 - max, 0);
}

Vec operator/(const Vec& other_vec, GLfloat length) {
	return std::move(Vec(other_vec.x / length, other_vec.y / length, other_vec.z / length));
}

GLfloat operator*(const Vec& vec_1, const Vec& vec_2) {
	return vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z;
}

Vec operator*(GLfloat length, const Vec& other_vec) {
	return Vec(length * other_vec.x, length * other_vec.y, length * other_vec.z);
}

Vec operator/(const Vec& vec_1, const Vec& vec_2) {
	return Vec(vec_1.y * vec_2.z - vec_1.z * vec_2.y, vec_1.z * vec_2.x - vec_1.x * vec_2.z, vec_1.x * vec_2.y - vec_1.y * vec_2.x);
}

Vec operator+(const Vec& vec_1, const Vec& vec_2) {
	return Vec(vec_1.x + vec_2.x, vec_1.y + vec_2.y, vec_1.z + vec_2.z);
}

Vec operator-(const Vec& vec_1, const Vec& vec_2) {
	return Vec(vec_1.x - vec_2.x, vec_1.y - vec_2.y, vec_1.z - vec_2.z);
}