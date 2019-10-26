#include "vect2d.h"


Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
}


Vector2::Vector2(double both) {
	this->x = both;
	this->y = both;
}


Vector2::Vector2(double X, double Y) {
	this->x = X;
	this->y = Y;
}

Vector2::~Vector2()
{
}
