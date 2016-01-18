#pragma once
#include <GL/glut.h>

class Vec {
public:
	GLfloat x, y, z;

	Vec();

	Vec(GLfloat x, GLfloat y, GLfloat z);

	Vec(const Vec& other);

	Vec(Vec&& other);

	Vec& operator=(const Vec& other);

	Vec& operator=(Vec&& other);

	GLfloat length();

	static Vec random(GLfloat max, int integer);
};

Vec operator / (const Vec& other_vec, GLfloat length);

GLfloat operator * (const Vec& vec_1, const Vec& vec_2);

Vec operator * (GLfloat length, const Vec& other_vec);

Vec operator / (const Vec& vec_1, const Vec& vec_2);

Vec operator + (const Vec& vec_1, const Vec& vec_2);

Vec operator - (const Vec& vec_1, const Vec& vec_2);
