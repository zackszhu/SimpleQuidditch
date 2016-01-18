#include "Tile.h"

Tile::Tile() {}

Tile::Tile(const Point& lt, const Point& rt, const Point& rb, const Point& lb)
	: leftTop(lt), rightTop(rt), leftBottom(lb), rightBottom(rb),
	ambient { 0.0f, 0.0f, 0.0f }, specular { 0.9f, 0.9f, 0.9f } {
	gradient = (lt - lb) + (lt - rt);
	gradient = gradient / gradient.length();
	if (gradient.z > 0)
		gradient = -1 * gradient;
	normal = (lt - rb) / (rt - lb);
	normal = normal / normal.length();
	if (normal.z < 0)
		normal = -1 * normal;
}

