#pragma once
#include "Point.h"
#include "Vector.h"
#include "BallGUI.h"

class Physics;
class Renderer;
const GLfloat ballRadius = 0.25;

class Ball {
protected:
	Vec velocity;
	Point pos;
	BallGUI ballGui;
	bool collidable;
	GLuint texture;
	GLfloat gravity;
	GLfloat rotation;
	Vec normal;
	double matrix[16];

public:
	friend Renderer;
	friend Physics;

	Point Pos() const;
	Vec Vel() const;

	virtual void move();

	void flipX();
	void flipY();
	void rotateBias(double x);
	void ToggleCollide();
	GLuint getTexture() const;

	Ball();
	Ball(const Point& pos, const Vec& velosity, const BallGUI& ballGui, bool collidable = true);
	Ball(const Point& pos, const BallGUI& ballGui, bool collidable = true);

	Ball(const Ball& other);

	Ball(Ball&& other);

	Ball& operator=(const Ball& other);

	Ball& operator=(Ball&& other);
	void stopDrop();
	void velocityZero();
};
