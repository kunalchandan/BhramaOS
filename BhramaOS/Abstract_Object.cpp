#include "Abstract_Object.h"
#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>

void Abstract_Object::step() {
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

void Abstract_Object::collide(Abstract_Object* m1, Abstract_Object* m2) {
	// Collisions will be restricted to ridgid body approximately inelastic collisions
	// Should I ever implement soft bodies this must change
	// TODO :: implement elastic collisions for soft bodies

	// m1*v1i   + m2*v2i   = m1*v1f   + m2*v2f
	// m1*v1i^2 + m2*v2i^2 = m1*v1f^2 + m2*v2f^2
	double m1vxi = m1->vx;
	double m1vyi = m1->vy;

	m1->vx = (((m1->m - m2->m) / (m1->m + m2->m))*m1->vx) + (((2 * m2->m) / (m1->m + m2->m))*m2->vx);
	m1->vy = (((m1->m - m2->m) / (m1->m + m2->m))*m1->vy) + (((2 * m2->m) / (m1->m + m2->m))*m2->vy);

	m2->vx = (((m2->m - m1->m) / (m2->m + m1->m))*m2->vx) + (((2 * m1->m) / (m2->m + m1->m))*m1vxi);
	m2->vy = (((m2->m - m1->m) / (m2->m + m1->m))*m2->vy) + (((2 * m1->m) / (m2->m + m1->m))*m1vyi);

}
