#include "WhiteBall.h"
#define    ImageWidth 512
#define    ImageHeight 512

GLfloat wAmbient[3] = { 0.1, 0.1, 0.1 };
GLfloat wSpecular[3] = { 0.5, 0.5, 0.5 };

GLubyte MatrixImage[ImageHeight][ImageWidth][3];

float InterLinear(float a, float b, float c) {
	return a*(1 - c) + b*c;
}

float Noise(int x) {
	x = (x << 13) ^ x;
	return (((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 2147483648.0);
}

float PerlinNoise(float x, float y, int width, int octaves, int seed, double period) {

	double a, b, value, freq, zone_x, zone_y;
	int s, box, num, step_x, step_y;
	float amplitude = period;
	int noisedata;

	freq = 1 / period;
	value = 0;

	for (s = 0; s<octaves; s++) {
		num = static_cast<int>(width*freq);
		step_x = static_cast<int>(x*freq);
		step_y = static_cast<int>(y*freq);
		zone_x = x*freq - step_x;
		zone_y = y*freq - step_y;
		box = step_x + step_y*num;
		noisedata = (box + seed);
		a = InterLinear(Noise(noisedata), Noise(noisedata + 1), zone_x);
		b = InterLinear(Noise(noisedata + num), Noise(noisedata + 1 + num), zone_x);
		value += InterLinear(a, b, zone_y)*amplitude;
		freq *= 4;
		amplitude /= 4;
	}
	return value;
}

void makeImage(void) {

	int x, y;
	int seed;
	int width;
	float  disp;

	for (y = 0; y< ImageWidth; y++) {
		for (x = 0; x<ImageHeight; x++) {
			width = 65536;
			seed = 42;

			disp = PerlinNoise(x, y, width, 5, seed, 128);

			MatrixImage[x][y][0] = disp;
			MatrixImage[x][y][1] = disp;
			MatrixImage[x][y][2] = disp;
		}
	}
}

void WhiteBall::textureInit() {
	makeImage();
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &MatrixImage[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glShadeModel(GL_FLAT);
}


WhiteBall::WhiteBall() {}

WhiteBall::~WhiteBall() {}

WhiteBall::WhiteBall(const Point & pos) :Ball(pos, Vec(-0.1, -0.1, 0.0), BallGUI(wAmbient, wSpecular), false) {
	textureInit();
}

void WhiteBall::move() {
	if (collidable) {
		Ball::move();
	}
}