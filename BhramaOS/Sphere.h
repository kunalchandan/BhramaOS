#pragma once
#include "Abstract_Object.h"
class Sphere :
	public Abstract_Object
{
public:
	double radius;
	Sphere(double radius, double mass, double charge, double posx, double posy, double velx, double vely, double theta, double omega);
	Sphere(double radius, double mass, double charge, Vector2 pos, Vector2 vel, double theta, double omega);

	void render() override;

	bool has_collided(Sphere* b);

	void hit_wall(double x_max, double y_max, double loss_ratio);

	~Sphere();
};

