#include "Rect.h"

Rect::Rect()
	: x(0.0),
	y(0.0),
	z(0.0),
	w(0.0),
	l(0.0),
	h(0.0) {}

Rect::Rect(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat l, GLfloat h)
	: x(x),
	y(y),
	z(z),
	w(w),
	l(l),
	h(h) {}

Rect::Rect(const Rect& other)
	: x(other.x),
	y(other.y),
	z(other.z),
	w(other.w),
	l(other.l),
	h(other.h) {}

Rect::Rect(Rect&& other)
	: x(other.x),
	y(other.y),
	z(other.z),
	w(other.w),
	l(other.l),
	h(other.h) {}

Rect& Rect::operator=(const Rect& other) {
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	l = other.l;
	h = other.h;
	return *this;
}

Rect& Rect::operator=(Rect&& other) {
	if (this == &other)
		return *this;
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	l = other.l;
	h = other.h;
	return *this;
}