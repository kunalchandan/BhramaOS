#pragma once
#include "Sphere.h"

struct Point {
	double x;
	double y;
	Point(double X, double Y) {
		x = X;
		y = Y;
	}
	Point() {
		x = 0;
		y = 0;
	}
};

class QuadTree
{
public:
	QuadTree();
	// Init with bounds x1,y1 top left; x2,y2 bot right
	QuadTree(double x1, double y1, double x2, double y2);
	void insert(Sphere *sp);


	Sphere *node;
	QuadTree *TL;
	QuadTree *TR;
	QuadTree *BL;
	QuadTree *BR;
	Point P_TL;
	Point P_BR;
	~QuadTree();

};

