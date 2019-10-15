#include "QuadTree.h"



QuadTree::QuadTree() {
	TL = NULL;
	TR = NULL;
	BL = NULL;
	BR = NULL;
	node = NULL;
}

QuadTree::QuadTree(double x1, double y1, double x2, double y2) {
	TL = NULL;
	TR = NULL;
	BL = NULL;
	BR = NULL;
	node = NULL;
	P_TL = Point(x1, y1);
	P_BR = Point(x2, y2);
}


void QuadTree::insert(Sphere *sp) {
	if(sp->)
}


QuadTree::~QuadTree()
{
	delete TL;
	delete TR;
	delete BL;
	delete BR;
	delete node;
}
