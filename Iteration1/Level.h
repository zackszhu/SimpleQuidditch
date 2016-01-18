#pragma once
#include "Desk.h"
#include "Ball.h"
#include "Text.h"
#include "Flag.h"
#include "Wall.h"
#include "Emitter.h"

struct Level {
	Text tips;
	Text spell;
	Desk desk;
	Point endPoint;
	Flag flag;
	std::vector<Ball*> balls;
	std::vector<Wall> walls;
	Emitter emitter;
	bool whiteStarted;
	int score;
	Level();
	Level(int level);
	void move();
	void startWhite();
};
