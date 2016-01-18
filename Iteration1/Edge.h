#pragma once
#include "Point.h"
#include <utility>

class Edge {
public:
	Point start;

	bool direction;

	Edge();

	Edge(const Point& start, bool direction);

	Edge(const Edge& other);

	Edge(Edge&& other);

	Edge& operator=(const Edge& other);

	Edge& operator=(Edge&& other);
};
