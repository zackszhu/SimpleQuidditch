#include "Edge.h"

Edge::Edge() {}

Edge::Edge(const Point& start, bool direction)
	: start(start),
	direction(direction) {}

Edge::Edge(const Edge& other)
	: start(other.start),
	direction(other.direction) {}

Edge::Edge(Edge&& other)
	: start(std::move(other.start)),
	direction(std::move(other.direction)) {}

Edge& Edge::operator=(const Edge& other) {
	if (this == &other)
		return *this;
	start = other.start;
	direction = other.direction;
	return *this;
}

Edge& Edge::operator=(Edge&& other) {
	if (this == &other)
		return *this;
	start = std::move(other.start);
	direction = std::move(other.direction);
	return *this;
}