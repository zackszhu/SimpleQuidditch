#include "Emitter.h"
#define EVENT_PARTICLE_NUM 5

Emitter::Emitter() {}

void Emitter::addEvent(const Point& position, const Vec& direction) {
	for (auto i = 0; i < EVENT_PARTICLE_NUM; i++) {
		auto randDir = Vec::random(0.05, 100);
		particles.push_back(Particle(position, direction + randDir));
	}
}

void Emitter::move() {
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		if (!it->isAlive()) {
			it = particles.erase(it);
			if (it == particles.end())
				break;
		}
		it->move();
	}
}

