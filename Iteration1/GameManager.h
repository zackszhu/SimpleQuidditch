#pragma once
#include <vector>
#include "Level.h"

class GameManager {
public:
	static GameManager & Instance();
	Level currentLevel;
	char keyPressed;
	bool levelFinish;

	GameManager(GameManager const&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager const&) = delete;
	GameManager& operator=(GameManager &&) = delete;

	// INIT part
	// Some initialization work
	void init();
	// API for level load in the future
	void loadLevel(int level = 0);

	// DISPLAY part
	// Some initialization of rendering every frame
	void displayInit();
	// Call renderer to render
	void render();

	// IDLE part
	// Call objects to move
	void move();
	// Call physics module to calculate
	void physics();

	// KEYBOARD part
	// Reshape the window
	void reshape(GLfloat width, GLfloat height);
	// Record key press and call according events
	void keyEvent();

	// LOGIC part
	// Calculate score
	void score();


private:
	std::vector<Level> levels;
	bool whiteStart;
	bool startBanner;
	long long time;

	void removeSpell();
	void rotateView(int num);
	void startWhite();

	GameManager();

	~GameManager();
};
