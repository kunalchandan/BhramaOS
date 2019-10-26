#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "vect2d.h"

class Abstract_Object
{
public:
	Vector2 p;
	Vector2 v;
	Vector2 a;
	Vector2 i;
	
	double theta, omega, alpha, zeta;

	double charge;
	double m;
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

	void step();

	void set_mass(double m);

	static void collide(Abstract_Object* a, Abstract_Object* b);

	static void gauss(Abstract_Object* a, Abstract_Object* b);

	virtual void render() = 0;

};

