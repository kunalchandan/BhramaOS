#pragma once
// TODO:: Insert Vector2 bool class
class Vector2
{
public:
	Vector2();
	Vector2(double both);
	Vector2(double x, double y);
	double x, y;

	Vector2& operator+=(Vector2 const &rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	Vector2& operator-=(Vector2 const &rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
	Vector2& operator*=(Vector2 const &rhs) {
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}
	Vector2& operator/=(Vector2 const &rhs) {
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}
	bool operator==(Vector2 const &rhs) {
		// Only does strict double comparisons 
		// If you want loose comparison within some comparison margin, we will talk
		// TODO:: Maybe implement loose comparisons
		if (this->x == rhs.x && this->y == rhs.y) {
			return true;
		}
		else {
			return false;
		}
	}

	~Vector2();
};

