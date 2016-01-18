#include "BallGUI.h"
#include <cstring>

BallGUI::BallGUI() {}

BallGUI::BallGUI(GLfloat ambient[3], GLfloat specular[3]) {
	this->ambient[0] = ambient[0];
	this->ambient[1] = ambient[1];
	this->ambient[2] = ambient[2];
	this->specular[0] = specular[0];
	this->specular[1] = specular[1];
	this->specular[2] = specular[2];
}

BallGUI::BallGUI(const BallGUI & ballGui) {
	this->ambient[0] = ballGui.ambient[0];
	this->ambient[1] = ballGui.ambient[1];
	this->ambient[2] = ballGui.ambient[2];
	this->specular[0] = ballGui.specular[0];
	this->specular[1] = ballGui.specular[1];
	this->specular[2] = ballGui.specular[2];
}

BallGUI::~BallGUI() {}