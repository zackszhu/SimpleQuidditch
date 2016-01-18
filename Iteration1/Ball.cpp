#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include "Ball.h"

GLfloat ambient[3] = { 0.3, 0.1, 0.1 };
GLfloat specular[3] = { 1.0, 0.4, 0.4 };
GLfloat g = 0.0015;

Ball::Ball() : collidable(false), texture(0), gravity(0), rotation(0) {}

Ball::Ball(const Point & pos, const Vec & velosity, const BallGUI & ballGui, bool collidable)
	: velocity(velosity),
	pos(pos),
	ballGui(ballGui),
	collidable(collidable),
	texture(0),
	gravity(g), rotation(0), matrix{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } {}

Ball::Ball(const Point& pos, const BallGUI& ballGui, bool collidable)
	: velocity(Vec::random(0.1, 100)),
	pos(pos),
	collidable(collidable),
	ballGui(ballGui),
	texture(0),
	gravity(g), rotation(0), matrix{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } {}

Ball::Ball(Ball&& other): velocity(std::move(other.velocity)),
                          pos(std::move(other.pos)),
                          ballGui(std::move(other.ballGui)),
                          collidable(other.collidable),
                          texture(other.texture),
                          gravity(other.gravity), rotation(other.rotation) {}

Ball::Ball(const Ball& other): velocity(other.velocity),
                               pos(other.pos),
                               ballGui(other.ballGui),
                               collidable(other.collidable),
                               texture(other.texture),
                               gravity(other.gravity), rotation(other.rotation) {}

Ball& Ball::operator=(const Ball& other) {
	if (this == &other)
		return *this;
	velocity = other.velocity;
	pos = other.pos;
	ballGui = other.ballGui;
	collidable = other.collidable;
	texture = other.texture;
	gravity = other.gravity;
	rotation = other.rotation;
	return *this;
}

Ball& Ball::operator=(Ball&& other) {
	if (this == &other)
		return *this;
	velocity = std::move(other.velocity);
	pos = std::move(other.pos);
	ballGui = std::move(other.ballGui);
	collidable = other.collidable;
	texture = other.texture;
	gravity = other.gravity;
	rotation = other.rotation;
	return *this;
}

void Ball::stopDrop() {
	velocity.z = velocity.z > 0 ? velocity.z : 0;
}

void Ball::move() {
	pos = pos + velocity;
	rotation = velocity.length() / ballRadius;
}

void Ball::flipX() {
	velocity.x *= -1;
}

void Ball::flipY() {
	velocity.y *= -1;
}

void Ball::rotateBias(double x) {
	auto theta = x / 180 * M_PI;
	auto tmpx = pos.x * cos(theta) + pos.y * sin(theta);
	pos.y = -pos.x * sin(theta) + pos.y * cos(theta);
	pos.x = tmpx;
	tmpx = velocity.x * cos(theta) + velocity.y * sin(theta);
	velocity.y = -velocity.x * sin(theta) + velocity.y * cos(theta);
	velocity.x = tmpx;
}

Point Ball::Pos() const {
	return pos;
}

Vec Ball::Vel() const {
	return velocity;
}

void Ball::ToggleCollide() {
	collidable = !collidable;
}

GLuint Ball::getTexture() const {
	return texture;
}

void Ball::velocityZero() {
	velocity = Vec(0, 0, 0);
	rotation = 0;
}
