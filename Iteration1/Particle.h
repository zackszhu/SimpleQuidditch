#pragma once
#include "Vector.h"
#include "Point.h"

class Renderer;

class Particle {
	Point position;
	Vec velosity;
	int lifetime;
public:
	friend Renderer;
	Particle();
	Particle(const Point& pos, const Vec& vel);
	
	void move();
	bool isAlive() const;
};
