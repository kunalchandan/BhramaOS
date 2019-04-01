#define _USE_MATH_DEFINES
#include "Sphere.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <math.h>


Sphere::Sphere(double radius, double mass, double charge, double posx, double posy, double velx, double vely) {
	this->charge = charge;
	this->radius = radius;
	set_mass(mass);
	
	this->px = posx;
	this->py = posy;

	this->vx = velx;
	this->vy = vely;
	this->ax = 0;
	this->ay = 0;
	this->ix = 0;
	this->iy = 0;
}

void Sphere::render() {
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	al_draw_filled_circle(this->px, this->py, this->radius, white);
}

bool Sphere::has_collided(Sphere* b) {
	// if distance^2 < bigRadius^2
	double dist2 = std::pow(this->px - b->px, 2) + std::pow(this->py - b->py, 2);
	double radi2 = std::pow(this->radius + b->radius, 2);
	if (dist2 < radi2) {
		// This code is causing my balls to disappear
		double dy = (this->py - b->py);
		double dx = (b->px - this->px);
		double angle = atan(dy / dx);
		if (((dx > 0) && (dy < 0)) || ((dx > 0) && (dy < 0))) {
			double sin = std::sin(angle) * (this->radius + b->radius);
			this->py = std::ceil(b->py + sin);

			double cos = std::cos(angle) * (this->radius + b->radius);
			this->px = std::ceil(b->px + cos);
		}
		else {
			double sin = std::sin(angle) * (this->radius + b->radius);
			this->py = std::ceil(b->py - sin);

			double cos = std::cos(angle) * (this->radius + b->radius);
			this->px = std::ceil(b->px - cos);
		}
		return true;
	} else {
		return false;
	}
}

void Sphere::hit_wall(double x_max, double y_max) {
	if (this->px + this->radius > x_max) {
		this->vx = -this->vx;
		this->px = x_max - this->radius;
	} 
	else if (this->px - this->radius < 0) {
		this->vx = -this->vx;
		this->px = this->radius;
	}
	if (this->py + this->radius > y_max) {
		this->vy = -this->vy;
		this->py = y_max - this->radius;
	} 
	else if (this->py - this->radius < 0) {
		this->vy = -this->vy;
		this->py = this->radius;
	}
}

// Basically nothing has to be done since I am not allocating dynamic memory
Sphere::~Sphere() {}

double atan(double x)
{
	return M_PI_4*x - x*(fabs(x) - 1)*(0.2447 + 0.0663*fabs(x));
}
