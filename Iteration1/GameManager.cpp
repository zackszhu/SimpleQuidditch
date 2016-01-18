#include "GameManager.h"
#include "Renderer.h"
#include "Physics.h"
#include "Camera.h"
//#include "Lighter.h"
#include <thread>
#include "Lighter.h"
#include "SoundManager.h"

const GLfloat rotatePerFrame = 1;

GameManager& GameManager::Instance() {
	static GameManager myInstance;
	return myInstance;
}

void GameManager::removeSpell() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	startBanner = false;
}

GameManager::GameManager() : keyPressed('\0'), levelFinish(false), whiteStart(false), startBanner(false), time(0) {
	levels.push_back(Level(1));
}

GameManager::~GameManager() {}

void GameManager::loadLevel(int level) {
	currentLevel = levels[level];
}

void GameManager::render(){
	Lighter::spotLightMove(currentLevel.balls.front()->Pos());
	Renderer::render(currentLevel.emitter);
	for each (auto wall in currentLevel.walls) {
		Renderer::render(wall);
	}
	Renderer::render(currentLevel.desk);
	auto q = 0.75;
	glAccum(GL_MULT, q);
	glAccum(GL_ACCUM, 1 - q);
	glAccum(GL_RETURN, 1.0);

	for each (auto ball in currentLevel.balls) {
		Renderer::render(*ball);
	}

	Renderer::render(currentLevel.endPoint);
	Renderer::render(currentLevel.tips);
	Renderer::render(currentLevel.score);
	Renderer::render(currentLevel.flag);
	if (startBanner)
		Renderer::render(currentLevel.spell);
	if (levelFinish)
		Renderer::render(Text("Game Finished!", Point(-0.8, 0.6, 0)));
}

void GameManager::move() {
	if (!levelFinish) {
		time += 1;
		currentLevel.move();
		auto wb = currentLevel.balls.front()->Pos();
		if ((Point(wb.x, wb.y, 0) - Point(-4.5, -4.5, 0)).length() < 2 * ballRadius) {
			levelFinish = true;
			SoundManager::playFinish();
		}
	}
	else {
		for (auto it = currentLevel.balls.begin(); it != currentLevel.balls.end(); ++it) {
			(*it)->velocityZero();
		}
	}
}

void GameManager::physics() {
	if (levelFinish)
		return;
	for (auto iter = currentLevel.balls.begin(); iter != currentLevel.balls.end(); ++iter) {
		bool down = true;
		if (iter == currentLevel.balls.begin())
			down = false;
		if (Physics::heightAmend(**iter, currentLevel.desk, down) && *iter != currentLevel.balls[1]) {
			(*iter)->stopDrop();
		}
	}

	if (whiteStart == true && currentLevel.whiteStarted == false) {
		auto flag = false;
		for (auto iter = currentLevel.balls.begin(); iter != currentLevel.balls.end(); ++iter) {
			if (iter == currentLevel.balls.begin())
				continue;
			auto whiteBall = currentLevel.balls.front();
			if (Physics::overlapDetection(*whiteBall, **iter)) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			currentLevel.startWhite();
			SoundManager::playWhiteBallStart();
		}
	}

	// TODO ghost drop overlap detect
	//auto flag = true;
	//for (auto iter = currentLevel.balls.begin(); iter != currentLevel.balls.end(); ++iter) {
	//	if (iter == currentLevel.balls.begin())
	//		continue;
	//	auto ghostBall = currentLevel.balls[1];
	//	if (Physics::overlapDetection(*ghostBall, **iter)) {
	//		flag = false;
	//		break;
	//	}
	//}
	//currentLevel.ghostDrop(flag);

	for (auto iter_1 = currentLevel.balls.begin(); iter_1 != currentLevel.balls.end(); ++iter_1) {
		for (auto iter_2 = currentLevel.balls.begin(); iter_2 != iter_1; ++iter_2) {
			Physics::collisionDetection(**iter_1, **iter_2);
		}
	}

	for (auto i = 0; i < 8; i++) {
		Physics::positionAmend(*currentLevel.balls[i], currentLevel.desk);
		Physics::collisionDetection(currentLevel.desk, *currentLevel.balls[i]);
	}

	for (auto iter = currentLevel.balls.begin(); iter != currentLevel.balls.end(); ++iter) {
		Physics::gravityApply(**iter, currentLevel.desk);
		Physics::normalCalc(**iter, currentLevel.desk);
	}
}

void GameManager::startWhite() {
	startBanner = true;
	std::thread t(&GameManager::removeSpell, this);
	t.detach();
	whiteStart = true;
}

void GameManager::score() {
	if (whiteStart) {
		auto whiteBall = currentLevel.balls.front();
		auto ghostBall = currentLevel.balls[1];
		if (Physics::overlapDetection(*whiteBall, *ghostBall)) {
			currentLevel.score += 100;
			SoundManager::playScore();
		}
		if (time % 120 == 0)
			currentLevel.score -= 5;
	}
}

void GameManager::rotateView(int num) {
	if (levelFinish)
		return;
	auto degree = num * rotatePerFrame;
	Camera::rotate(degree);
	//currentLevel.tips.rotateBias(-num * rotatePerFrame);
	for (auto i = 0; i < 8; i++) {
		currentLevel.balls[i]->rotateBias(-degree);
	}
	currentLevel.flag.rotateBias(-degree);
}

void GameManager::reshape(GLfloat width, GLfloat height) {
	Camera::setProject(width, height);
}

void GameManager::keyEvent() {
	switch (keyPressed) {
	case 'a':
		rotateView(-1);
		break;
	case 'd':
		rotateView(1);
		break;
	case ' ':
		startWhite();
		break;
	case 'w':
		Lighter::spotLightSwitch();
		break;
	}
	keyPressed = '\0';
}

void GameManager::displayInit() {
	Camera::setModel();
	Renderer::displayInit();
}

void GameManager::init() {
	Renderer::init();
}