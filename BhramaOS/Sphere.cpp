#define _USE_MATH_DEFINES
#include "Sphere.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <cmath>
#include <math.h>


Sphere::Sphere(double radius, double mass, double charge, double posx, double posy, double velx, double vely, double theta, double omega) {
	this->charge = charge;
	this->radius = radius;
	set_mass(mass);
	
	this->theta = theta;
	this->omega = omega;
	this->alpha = 0;
	this->zeta  = 0;

	this->p.x = posx;
	this->p.y = posy;

	this->v.x = velx;
	this->v.y = vely;
	this->a.x = 0;
	this->a.y = 0;
	this->i.x = 0;
	this->i.y = 0;
}

Sphere::Sphere(double radius, double mass, double charge, Vector2 pos, Vector2 vel, double theta, double omega) {
	this->charge = charge;
	this->radius = radius;
	set_mass(mass);

	this->theta = theta;
	this->omega = omega;
	this->alpha = 0;
	this->zeta  = 0;

	this->p = pos;

	this->v = vel;
	this->a = 0;
	this->i = 0;
}

void Sphere::render() {
	al_draw_filled_circle(this->p.x, this->p.y, this->radius, this->color);
	for(int x = this->radius; x > 1; x -= 10){
		// Markers for showing rotation
		al_draw_filled_circle(this->p.x + x * cos(this->theta), 
							  this->p.y + x * sin(this->theta), 
							  3, al_map_rgb(0, 0, 0));
	}
}

bool Sphere::has_collided(Sphere* b) {
	// if distance^2 < bigRadius^2
	//TODO:: Elastic vs Inelastic collision
	// Calculate Inelastic and make final velocities a percenatage of each.
	double dist2 = std::pow(this->p.x - b->p.x, 2) + std::pow(this->p.y - b->p.y, 2);
	double radi2 = std::pow(this->radius + b->radius, 2);
	if (dist2 < radi2) {
		Vector2 d = this->p - b->p;

		double dist = sqrt(dist2);
		double radi = this->radius + b->radius;
		double ratio = (radi + 1) / dist;

		this->p = b->p + (d * ratio);
		return true;
	} else {
		return false;
	}
}

void Sphere::hit_wall(double x_max, double y_max, double loss_ratio) {
	if (this->p.x + this->radius > x_max) {
		this->v.x = -this->v.x*loss_ratio;
		this->p.x = x_max - this->radius;
	} 
	else if (this->p.x - this->radius < 0) {
		this->v.x = -this->v.x*loss_ratio;
		this->p.x = this->radius;
	}
	if (this->p.y + this->radius > y_max) {
		this->v.y = -this->v.y*loss_ratio;
		this->p.y = y_max - this->radius;
	} 
	else if (this->p.y - this->radius < 0) {
		this->v.y = -this->v.y*loss_ratio;
		this->p.y = this->radius;
	}
}

// Basically nothing has to be done since I am not allocating dynamic memory
Sphere::~Sphere() {}

double atan(double x)
{
	return M_PI_4*x - x*(fabs(x) - 1)*(0.2447 + 0.0663*fabs(x));
}
