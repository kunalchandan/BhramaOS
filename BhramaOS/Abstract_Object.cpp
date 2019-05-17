#include "Abstract_Object.h"
#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>

void Abstract_Object::step() {
	alpha += zeta;
	omega += alpha;
	theta += omega;

	ax += ix;
	vx += ax;
	px += vx;

	ay += iy;
	vy += ay;
	py += vy;
}

void Abstract_Object::set_mass(double m) {
	this->m = std::max(std::numeric_limits<double>::epsilon(), m);
}


void Abstract_Object::gauss(Abstract_Object* a, Abstract_Object* b) {
	if (a->charge == 0 || b->charge == 0) {
		double k = 100000;

		double r2 = pow(a->px - b->px, 2) + pow(a->py - b->py, 2);
		double f_e = k*(a->charge*b->charge)/r2;
		double unit[2] = {(a->px - b->px)/r2, (a->py - b->py)/r2};
		double f_e_ab = f_e / b->m;
		double f_e_ba = f_e / a->m;

		b->ax += f_e_ab;
		a->ax -= f_e_ba;

		b->ay += f_e_ab;
		a->ay -= f_e_ba;
	}
}

void Abstract_Object::collide(Abstract_Object* m1, Abstract_Object* m2) {
	// Collisions will be restricted to ridgid body approximately inelastic collisions
	// Should I ever implement soft bodies this must change
	// TODO :: implement elastic collisions for soft bodies
	
	// Inelastic Collisions
	// vfnet = (m1*v1 + m2*v2)/(m1+m2)
	// double vfx_net = ((m1->m * m1->vx) + (m2->m * m2->vx)) / (m1->m + m2->m);
	
	// Elastic Collisions
	// m1*v1i   + m2*v2i   = m1*v1f   + m2*v2f
	// m1*v1i^2 + m2*v2i^2 = m1*v1f^2 + m2*v2f^2

	// Implementing angular velocity colilisions



	double m1wi = m1->omega;

	m1->omega = (((m1->m - m2->m) / (m1->m + m2->m))*m1->omega) + (((2 * m2->m) / (m1->m + m2->m))*m2->omega);

	m2->omega = (((m2->m - m1->m) / (m2->m + m1->m))*m2->omega) + (((2 * m1->m) / (m2->m + m1->m))*m1wi);


	double m1vxi = m1->vx;
	double m1vyi = m1->vy;

	m1->vx = (((m1->m - m2->m) / (m1->m + m2->m))*m1->vx) + (((2 * m2->m) / (m1->m + m2->m))*m2->vx);
	m1->vy = (((m1->m - m2->m) / (m1->m + m2->m))*m1->vy) + (((2 * m2->m) / (m1->m + m2->m))*m2->vy);

	m2->vx = (((m2->m - m1->m) / (m2->m + m1->m))*m2->vx) + (((2 * m1->m) / (m2->m + m1->m))*m1vxi);
	m2->vy = (((m2->m - m1->m) / (m2->m + m1->m))*m2->vy) + (((2 * m1->m) / (m2->m + m1->m))*m1vyi);

}
