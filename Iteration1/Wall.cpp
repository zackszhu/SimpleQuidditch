#include "Wall.h"
#include "GL/SOIL.h"

GLuint loadFlagImage(std::string filename) {
	GLuint tex_2d = SOIL_load_OGL_texture(("imgs/" + filename).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (tex_2d == 0)
		return -1;
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	return tex_2d;
}


GLuint Wall::getTexture() const {
	return texture;
}

Wall::Wall() : texture(0) {}

Wall::Wall(const Vec& left_bottom, const Vec& right_bottom, const Vec& right_top, const Vec& left_top, std::string filename)
	: leftTop(left_top),
	rightTop(right_top),
	leftBottom(left_bottom),
	rightBottom(right_bottom),
	texture(loadFlagImage(filename)) {}
