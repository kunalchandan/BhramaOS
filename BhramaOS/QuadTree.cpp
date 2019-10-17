#include "QuadTree.h"
#include "vect2d.h"
#include "sim_consts.h"

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
	V_TL = Vector2(x1, y1);
	V_BR = Vector2(x2, y2);
}

QuadTree::QuadTree(Vector2 topLeft, Vector2 bottomRight) {
	TL = NULL;
	TR = NULL;
	BL = NULL;
	BR = NULL;
	node = NULL;
	V_TL = topLeft;
	V_BR = bottomRight;
}


void QuadTree::insert(Sphere *sp) {
	if (!inQuad(sp->p)) {
		throw "Invalid state reached.";
	}
	if (fabs(this->V_TL.x - this->V_BR.x) <= CELL_EPSILON &&
		fabs(this->V_TL.y - this->V_BR.y) <= CELL_EPSILON) {
		if (node == NULL) {
			node = sp;
		}
		return;
	}
	Vector2 centre = ((this->V_TL + this->V_BR) / 2);
	bool y_hat = centre.y >= sp->p.y;
	bool x_hat = centre.x >= sp->p.x;
	if (x_hat && y_hat) {
		// Top right? depends on your axis lol
		if (this->TL == NULL) {
			TL = new QuadTree(this->V_TL, centre);
		}
		this->TL->insert(sp);
	}
	else if (x_hat && !y_hat) {
		if (this->BL == NULL) {
			TL = new QuadTree(this->V_TL.x, centre.y,
							  centre.x, this->V_BR.y);
		}
		this->TL->insert(sp);
	}
	else if (!x_hat && y_hat) {
		if (this->TR == NULL) {
			TL = new QuadTree(this->V_TL, centre);
		}
		this->TL->insert(sp);
	}
	else if (x_hat && !y_hat) {
		if (this->BL == NULL) {
			TL = new QuadTree(this->V_TL, centre);
		}
		this->TL->insert(sp);
	}
}


bool QuadTree::inQuad(Vector2 v) {
	return (v.x >= this->V_TL.x 
		&&  v.x <= this->V_BR.x
		&&  v.y >= this->V_TL.y
		&&  v.y <= this->V_BR.y);
}


QuadTree::~QuadTree()
{
	delete TL;
	delete TR;
	delete BL;
	delete BR;
	delete node;
}
