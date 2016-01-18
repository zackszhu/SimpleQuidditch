#include "Physics.h"
#include <cmath>

bool Physics::collisionDetection(const Edge& edge, Ball& ball) {
	if (edge.direction == true) { // x direction
		if (abs(ball.Pos().y - edge.start.y) <= ballRadius) {
			ball.flipY();
			return true;
		}
	}
	else {
		if (abs(ball.Pos().x - edge.start.x) <= ballRadius) {
			ball.flipX();
			return true;
		}
	}
	return false;
}

void Physics::collisionDetection(Ball& ball_1, Ball& ball_2) {
	if (!(ball_1.collidable && ball_2.collidable))
		return;
//	if (abs(floor(ball_1.pos.x) - floor(ball_2.pos.x)) > 1 || abs(floor(ball_2.pos.y) - floor(ball_1.pos.y)) > 1)
//		return;
	auto disVec = ball_1.Pos() - ball_2.Pos();
	auto dis = disVec.length();
	if (dis <= 2 * ballRadius) {
		auto vertical = disVec / dis;
		auto horizontal = Vec(vertical.y, -vertical.x, vertical.z);
		auto v1 = (ball_2.velocity * vertical) * vertical + (ball_1.velocity * horizontal) * horizontal;
		auto v2 = (ball_1.velocity * vertical) * vertical + (ball_2.velocity * horizontal) * horizontal;
		auto v = v1 - v2;
		auto scale = (2 * ballRadius - dis) / v.length();
		ball_1.pos = ball_1.pos + (scale * v1);
		ball_2.pos = ball_2.pos + (scale * v2);
		ball_1.velocity = std::move(v1);
		ball_2.velocity = std::move(v2);

	}
}

void Physics::collisionDetection(const Desk& desk, Ball& ball) {
	for each (auto edge in desk.edges) {
		collisionDetection(edge, ball);
	}
}

bool Physics::overlapDetection(const Ball& ball_1, const Ball& ball_2) {
	auto disVec = ball_1.Pos() - ball_2.Pos();
	auto dis = disVec.length();
	return dis <= 2 * ballRadius;
}

void Physics::positionAmend(Ball& ball, const Desk& desk) {
	for each (auto edge in desk.edges) {
		if (edge.start.x < 0)
			ball.pos.x = ball.pos.x > edge.start.x + ballRadius? ball.pos.x : edge.start.x + ballRadius;
		else 
			ball.pos.x = ball.pos.x < edge.start.x - ballRadius ? ball.pos.x : edge.start.x - ballRadius;

		if (edge.start.y < 0)
			ball.pos.y = ball.pos.y > edge.start.y + ballRadius ? ball.pos.y : edge.start.y + ballRadius;
		else
			ball.pos.y = ball.pos.y < edge.start.y - ballRadius ? ball.pos.y : edge.start.y - ballRadius;
	}
}

bool Physics::heightAmend(Ball& ball, const Desk& desk, bool down) {
	int xIndex = floor(ball.Pos().x) + 5;
	int yIndex = floor(ball.Pos().y) + 5;
	if (xIndex < 0 || xIndex >= 10 || yIndex < 0 || yIndex >= 10)
		return false;
	Tile t = desk.tiles[xIndex][yIndex];
	GLfloat zz = t.leftTop.z + (ball.Pos().x - xIndex + 5) * (t.rightTop.z - t.leftTop.z) + (ball.Pos().y - yIndex + 5) * (t.leftBottom.z - t.leftTop.z) + abs((ballRadius - Vec(0, 0, ballRadius) * t.normal) / t.normal.z);
	if (ball.Pos().z < zz) {
		ball.pos.z = zz;
		return true;
	}
	if (ball.Pos().z > zz && !down && !ball.collidable) {
		GLfloat l = abs((Vec(0, 0, ball.Pos().z - zz) * t.normal) / t.normal.z);
		ball.pos.z = zz;
		return true;
	}
	return false;

}

void Physics::gravityApply(Ball& ball, const Desk& desk) {
	if (!ball.collidable)
		return;
	int xIndex = floor(ball.Pos().x) + 5;
	int yIndex = floor(ball.Pos().y) + 5;
	if (xIndex < 0 || xIndex >= 10 || yIndex < 0 || yIndex >= 10)
		return;
	Tile t = desk.tiles[xIndex][yIndex];
	GLfloat zz = t.leftTop.z + (ball.Pos().x - xIndex + 5) * (t.rightTop.z - t.leftTop.z) + (ball.Pos().y - yIndex + 5) * (t.leftBottom.z - t.leftTop.z) + abs((ballRadius - Vec(0, 0, ballRadius) * t.normal) / t.normal.z);
	if (ball.Pos().z > zz) {
		ball.velocity.z -= ball.gravity;
	}
	if (ball.Pos().z == zz) {
		GLfloat l = Vec(0, 0, -ball.gravity) * t.gradient;
		ball.velocity = ball.velocity + l * t.gradient;
	}
}

void Physics::normalCalc(Ball& ball, const Desk& desk) {
	int xIndex = floor(ball.Pos().x) + 5;
	int yIndex = floor(ball.Pos().y) + 5;
	if (xIndex < 0 || xIndex >= 10 || yIndex < 0 || yIndex >= 10)
		return;
	Tile t = desk.tiles[xIndex][yIndex];
	ball.normal = ball.velocity / t.normal;
}
