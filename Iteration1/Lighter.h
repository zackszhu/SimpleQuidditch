#pragma once

class Point;

class Lighter {
	static bool lightSwitch;
public:
	static void init();
	static void spotLightMove(const Point& pos);
	static void spotLightSwitch();
};
