#pragma once
#include <cmath>
#include "Sphere.h"
#include "vect2d.h"

class QuadTree
{
private:
	int remove(QuadTree *q);

public:
	QuadTree();
	// Init with bounds x1,y1 top left; x2,y2 bot right
	QuadTree(double x1, double y1, double x2, double y2);
	QuadTree(Vector2 topLeft, Vector2 bottomRight);

	Sphere* search(Vector2 v);
	void insert(Sphere *sp);
	void move(Sphere *sp);
	bool inQuad(Vector2 v);

	bool visited;
	short level;
	Sphere *node;
	QuadTree *PARENT;
	QuadTree *TL;
	QuadTree *TR;
	QuadTree *BL;
	QuadTree *BR;
	Vector2 V_TL;
	Vector2 V_BR;
	Vector2 CENT;

	bool operator==(QuadTree &rhs) {
		// There is no reson comparison for Quadtrees should require anything looser/with margins
		if (this->V_TL == rhs.V_TL && this->V_BR == rhs.V_BR) {
			return true;
		}
		else {
			return false;
		}
	}
	~QuadTree();

};

