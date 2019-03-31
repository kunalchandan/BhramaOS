#pragma once
class Abstract_Object
{
public:
	double px, py;
	double vx, vy;
	double ax, ay;
	double ix, iy;
	double charge;
	double m;

	void step();

	void set_mass(double m);

	static void collide(Abstract_Object* a, Abstract_Object* b);

	virtual void render() = 0;
};

