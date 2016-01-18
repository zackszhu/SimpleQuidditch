#include "MovingBall.h"

GLfloat mAmbient[3] = { 0.3, 0.1, 0.1 };
GLfloat mSpecular[3] = { 1.0, 0.4, 0.4 };

MovingBall::MovingBall(const Point& pos) :Ball(pos, BallGUI(mAmbient, mSpecular), true) {}
