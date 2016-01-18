#pragma once
#include "Edge.h"
#include "Ball.h"
#include "Desk.h"

class Physics {
public:
	static bool collisionDetection(const Edge& edge, Ball& ball);
	static void collisionDetection(Ball& ball_1, Ball& ball_2);
	static void collisionDetection(const Desk& desk, Ball& ball);
	static bool overlapDetection(const Ball& ball_1, const Ball& ball_2);
	static void positionAmend(Ball& ball, const Desk& desk);
	static bool heightAmend(Ball& ball, const Desk& desk, bool down);
	static void gravityApply(Ball& ball, const Desk& desk);
	static void normalCalc(Ball& ball, const Desk& desk);
};
