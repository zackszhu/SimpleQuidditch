#pragma once
#include <string>
#include "Point.h"

class Text {
public:
	std::string content;
	Point pos;

	Text(const std::string content, const Point& pos);
	void rotateBias(double x);
};
