#define _USE_MATH_DEFINES
#include <cmath>
#include "Text.h"

Text::Text(const std::string content, const Point& pos) :content(content), pos(pos) {}

void Text::rotateBias(double x) {
	auto theta = x / 180 * M_PI;
	pos.x = pos.x * cos(theta) + pos.y * sin(theta);
	pos.y = -pos.x * sin(theta) + pos.y * cos(theta);

}