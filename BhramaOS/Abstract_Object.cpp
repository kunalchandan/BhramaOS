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

	a += i;
	v += a;
	p += v;
}

void Abstract_Object::set_mass(double m) {
	this->m = std::max(std::numeric_limits<double>::epsilon(), m);
}

// This function must be run only ONCE per pair of objects
void Abstract_Object::gauss(Abstract_Object* a, Abstract_Object* b) {
	// As of right now this is simply an approximation by using:
	// F = (k*q_1*q_2)/r^2
	// This should eventually do something like:
	// dF = (k*dq_1*dq_2)/r^2
	// and find the integral value, and finally apply the net force. 
	// Keep in mind this method requires knowledge of the charge distribution.
	if ( ! ((a->charge == 0) || (b->charge == 0)) ) {
		// Consider storing this constant *k* elsewhere as it is a 'universal' constant
		double k = 1;

		double r2 = pow(a->p.x - b->p.x, 2) + pow(a->p.x - b->p.x, 2);
		double f_e = k*(a->charge*b->charge)/r2;
		double f_e_ab = f_e / b->m;
		double f_e_ba = f_e / a->m;

		b->a += f_e_ab;
		a->a += f_e_ba;
	}
}

// This function must be run only ONCE per pair of objects
void Abstract_Object::collide(Abstract_Object* m1, Abstract_Object* m2) {
	// Collisions will be restricted to ridgid body approximately inelastic collisions
	// Should I ever implement soft bodies this must change
	// TODO :: implement elastic collisions for soft bodies
	
	// Inelastic Collisions
	// vfnet = (m1*v1 + m2*v2)/(m1+m2)
	// double vfx_net = ((m1->m * m1->v.x) + (m2->m * m2->v.x)) / (m1->m + m2->m);
	
	// Elastic Collisions
	// m1*v1i   + m2*v2i   = m1*v1f   + m2*v2f
	// m1*v1i^2 + m2*v2i^2 = m1*v1f^2 + m2*v2f^2

	// Implementing angular velocity colilisions



	double m1wi = m1->omega;

	m1->omega = (((m1->m - m2->m) / (m1->m + m2->m))*m1->omega) + (((2 * m2->m) / (m1->m + m2->m))*m2->omega);

	m2->omega = (((m2->m - m1->m) / (m2->m + m1->m))*m2->omega) + (((2 * m1->m) / (m2->m + m1->m))*m1wi);

	Vector2 m1vi = m1->v;

	m1->v = (((m1->m - m2->m) / (m1->m + m2->m))*m1->v) + (((2 * m2->m) / (m1->m + m2->m))*m2->v);

	m2->v = (((m2->m - m1->m) / (m2->m + m1->m))*m2->v) + (((2 * m1->m) / (m2->m + m1->m))*m1vi);
	
}
