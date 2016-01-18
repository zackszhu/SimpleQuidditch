#pragma once
#include <list>
#include "Particle.h"

class Renderer;

class Emitter {
	std::list<Particle> particles;
public:
	friend Renderer;

	Emitter();
	void addEvent(const Point& position, const Vec& direction);
	void move();
};
