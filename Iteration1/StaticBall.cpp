#include "StaticBall.h"

GLfloat sAmbient[3] = { 0.1, 0.3, 0.1 };
GLfloat sSpecular[3] = { 0.4, 1.0, 0.4 };

StaticBall::StaticBall() {}


StaticBall::~StaticBall() {}

StaticBall::StaticBall(const Point& pos) :Ball(pos, Vec(0.0, 0.0, 0.0),  BallGUI(sAmbient, sSpecular), false) {}