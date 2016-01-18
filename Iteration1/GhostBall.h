#pragma once
#include "Ball.h"
class GhostBall :
	public Ball {
	int turns;
public:
	GhostBall();
	~GhostBall();

	GhostBall(const Point& pos);

	virtual void move() override;

	bool droppable;

};
