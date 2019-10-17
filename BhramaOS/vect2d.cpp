#include "vect2d.h"



Vector2::Vector2(double both) {
	this->x = both;
	this->y = both;
}


Vector2::Vector2(double X, double Y) {
	this->x = X;
	this->y = Y;
}

Vector2 operator+(Vector2 const &v1, Vector2 const &v2) {
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}
Vector2 operator-(Vector2 const &v1, Vector2 const &v2) {
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}
Vector2 operator*(Vector2 const &v1, Vector2 const &v2) {
	return Vector2(v1.x * v2.x, v1.y * v2.y);
}
Vector2 operator/(Vector2 const &v1, Vector2 const &v2) {
	return Vector2(v1.x / v2.x, v1.y / v2.y);
}
bool operator==(Vector2 const &v1, Vector2 const &v2) {
	return (v1.x == v2.x) && (v1.y == v2.y);
}

Vector2::~Vector2()
{
}
