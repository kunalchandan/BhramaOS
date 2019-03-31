#pragma once
#include "Abstract_Object.h"
class Sphere :
	public Abstract_Object
{
public:
	double radius;
	Sphere(double radius, double mass, double charge, double posx, double posy, double velx, double vely);
	
	void render() override;

	bool has_collided(Sphere* b);

	void hit_wall(double x_max, double y_max);

	~Sphere();
};

