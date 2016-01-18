#pragma once
#include "Ball.h"
class StaticBall :
	public Ball {
public:
	StaticBall();
	~StaticBall();

	explicit StaticBall(const Point& pos);

};

