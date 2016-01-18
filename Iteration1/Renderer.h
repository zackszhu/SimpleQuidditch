#pragma once
class Tile;
class Particle;
class Emitter;
class Wall;
class Point;
class Ball;
class Desk;
class Text;
class Flag;

class Renderer {
	static void renderOutline(const Desk& desk);
	static void renderFill(const Desk& desk);
public:
	static void init();
	static void displayInit();
	static void render(const Desk& desk);
	static void render(const Text& text);
	static void render(Ball& ball);
	static void render(const Point& point);
	static void render(int score);
	static void render(Flag& flag);
	static void render(const Wall& wall);
	static void render(const Emitter& emitter);
	static void render(const Particle& particle);
	static void render(const Tile& tile);
};
