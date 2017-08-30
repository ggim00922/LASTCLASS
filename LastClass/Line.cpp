//Line.cpp

#include "Line.h"

Line::Line() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Line::~Line() {
}

Line::Line(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Line::Line(const Line& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Line& Line::operator = (const Line& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;

	return *this;
}

Figure* Line::Clone() {
	return new Line(*this);
}


#include <iostream>
using namespace std;

