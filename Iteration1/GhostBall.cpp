#include "GhostBall.h"

GLfloat gAmbient[3] = { 0.1, 0.1, 0.3 };
GLfloat gSpecular[3] = { 0.4, 0.4, 1.0 };

GhostBall::GhostBall() {}

GhostBall::~GhostBall() {}

GhostBall::GhostBall(const Point & pos) :Ball(pos, BallGUI(gAmbient, gSpecular), false), turns(0) {
	gravity = 0;
}

void GhostBall::move() {
	if (pos.z <= 0 && velocity.z < 0) {
		pos.z = 0;
		velocity = Vec::random(0.05, 100);
		collidable = true;
	}
	if (pos.z > 3) {
		pos.z = 3;
		velocity = Vec::random(0.05, 100);
	}
	if (++turns > 800 && pos.z > 0) {
		velocity.z = -0.05;
	}
	if ( ++turns > 1200) {
		turns = 0;
		velocity.z = 0.05;
		collidable = false;
	}
	if (++turns % 200 == 0 && pos.z >= 3) {
		velocity = Vec::random(0.05, 100);
	}
	Ball::move();
}