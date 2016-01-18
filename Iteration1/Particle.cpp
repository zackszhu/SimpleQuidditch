#include "Particle.h"
#include <cstdlib>

Particle::Particle() : lifetime(0) {}

Particle::Particle(const Point& pos, const Vec& vel)
	: position(pos), velosity(vel), lifetime(10 + rand() % 4 - 2) {}

bool Particle::isAlive() const {
	return lifetime > 0;
}

void Particle::move() {
	position = position + velosity;
	lifetime--;
}
