#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.h"

float Camera::viewRotation = 45 * M_PI / 180;

void Camera::setProject(GLfloat width, GLfloat height) {
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -float(height) / width, float(height) / width, 2.0, 3000.0);

}

void Camera::setModel() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15.0 * cos(viewRotation), 15.0 * sin(viewRotation), 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

void Camera::rotate(GLfloat radius) {
	viewRotation += radius / 180 * M_PI;
}