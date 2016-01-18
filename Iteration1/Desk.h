#pragma once
#include <vector>
#include "Rect.h"
#include "Edge.h"
#include "Tile.h"

class Physics;
class Renderer;

class Desk {
	std::vector<Rect> rects;
	std::vector<Edge> edges;
	std::vector<std::vector<Tile>> tiles;

	void addEdges(GLfloat x, GLfloat y, GLfloat w, GLfloat l);

public:
	friend Renderer;
	friend Physics;

	Desk(int level = 1);
};
