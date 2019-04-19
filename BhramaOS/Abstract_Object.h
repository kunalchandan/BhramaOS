#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Abstract_Object
{
public:
	double px, py;
	double vx, vy;
	double ax, ay;
	double ix, iy;
	double charge;
	double m;
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

	void step();

	void set_mass(double m);

	static void collide(Abstract_Object* a, Abstract_Object* b);

	virtual void render() = 0;
};

