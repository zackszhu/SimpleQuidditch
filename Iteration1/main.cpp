#include <GL\glut.h>
#include "GameManager.h"

const int fps = 60;

void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Simple Quidditch");

	GameManager::Instance().init();
	GameManager::Instance().loadLevel(0);
}

void displayCB() {
	GameManager::Instance().displayInit();

	GameManager::Instance().render();

	glutSwapBuffers();
}

void reshapeCB(GLint newWidth, GLint newHeight) {
	glClearAccum(0.0, 0.0, 0.0, 1.0);
	glClear(GL_ACCUM_BUFFER_BIT);
	GameManager::Instance().reshape(newWidth, newHeight);
}

void idleCB(int t) {
	GameManager::Instance().keyEvent();
	GameManager::Instance().physics();
	GameManager::Instance().move();
	GameManager::Instance().score();

	glutTimerFunc(500 / fps, idleCB, 0);
}

void keyboardCB(unsigned char key, int x, int y) {
	GameManager::Instance().keyPressed = key;
}

void postCB(int t) {
	glutPostRedisplay();
	glutTimerFunc(500 / fps, postCB, 0);
}

int main() {
	init();
	glutDisplayFunc(displayCB);
	glutReshapeFunc(reshapeCB);
	glutTimerFunc(500 / fps, postCB, 0);
	glutTimerFunc(500 / fps, idleCB, 0);
	//glutIdleFunc(idleCB);
	glutKeyboardFunc(keyboardCB);
	glutMainLoop();
}