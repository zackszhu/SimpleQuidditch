#include "Level.h"
#include "WhiteBall.h"
#include "GhostBall.h"
#include <ctime>
#include "MovingBall.h"
#include "StaticBall.h"

void Level::move() {
	for (auto iter = balls.begin(); iter != balls.end(); ++iter) {
		(*iter)->move();
	}
	if (whiteStarted) {
		auto wb = balls.front();
		if (wb->Vel().length() > 0.075)
			emitter.addEvent(wb->Pos() + Vec(0, 0, 0.25), -1 * wb->Vel());
	}
	emitter.move();
	flag.move();
}

void Level::startWhite() {
	balls[0]->ToggleCollide();
	whiteStarted = true;
}

//void Level::ghostDrop(bool flag) {
//	auto ghostBall = dynamic_cast<GhostBall*>(balls[1]);
//	ghostBall->droppable = flag;
//}

Level::Level() :tips("", Point()), spell("", Point()) {}

Level::Level(int level)
	:flag(), desk(), balls(12), whiteStarted(false),
	tips("Press space to start the ball, A/D to rotate", Point(-0.8, 0.8, 0)),
	score(0), spell("Oppugno!!!", Point(0, -0.7, 0)),
	walls(6) {
	srand(static_cast<unsigned>(time(nullptr)));
	balls[0] = new WhiteBall(Point(4.5, 4.5, 0.0));
	balls[1] = new GhostBall(Point(0.0, 0.0, 3.0));
	balls[2] = new MovingBall(Point(1.0, 1.0, 0.0));
	balls[3] = new MovingBall(Point(-1.0, 1.0, 0.0));
	balls[4] = new MovingBall(Point(1.0, -1.0, 0.0));
	balls[5] = new MovingBall(Point(-1.0, -1.0, 0.0));
	balls[6] = new MovingBall(Point(2.0, 1.0, 0.0));
	balls[7] = new MovingBall(Point(.0, 2.0, 0.0));
	balls[8] = new StaticBall(Point(5.5, -5.5, 0.5));
	balls[9] = new StaticBall(Point(5.5, 5.5, 0.5));
	balls[10] = new StaticBall(Point(-5.5, 5.5, 0.5));
	balls[11] = new StaticBall(Point(-5.5, -5.5, 0.5));
	endPoint = std::move(Point(-4.5, -4.5, 0.11));
	walls[0] = Wall(Vec(-32, -32, -32), Vec(-32, 32, -32), Vec(-32, 32, 32), Vec(-32, -32, 32), "back.jpg");
	walls[1] = Wall(Vec(-32, 32, -32), Vec(32, 32, -32), Vec(32, 32, 32), Vec(-32, 32, 32), "right.jpg");
	walls[2] = Wall(Vec(32, 32, -32), Vec(32, -32, -32), Vec(32, -32, 32), Vec(32, 32, 32), "front.jpg");
	walls[3] = Wall(Vec(32, -32, -32), Vec(-32, -32, -32), Vec(-32, -32, 32), Vec(32, -32, 32), "left.jpg");
	walls[4] = Wall(Vec(32, 32, 32), Vec(32, -32, 32), Vec(-32, -32, 32), Vec(-32, 32, 32), "up.jpg");
	walls[5] = Wall(Vec(-32, 32, -32), Vec(-32, -32, -32), Vec(32, -32, -32), Vec(32, 32, -32), "down.jpg");
}
