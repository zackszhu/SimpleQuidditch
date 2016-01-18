#pragma once
#include "Ball.h"
class WhiteBall :
	public Ball {
	void textureInit();
public:
	WhiteBall();
	~WhiteBall();
	WhiteBall(const Point& pos);
	virtual void move() override;
};
