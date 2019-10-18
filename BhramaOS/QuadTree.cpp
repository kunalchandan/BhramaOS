#include "QuadTree.h"
#include "vect2d.h"
#include "sim_consts.h"

QuadTree::QuadTree() {
	TL = NULL;
	TR = NULL;
	BL = NULL;
	BR = NULL;
	node = NULL;
	PARENT = NULL;
}

QuadTree::QuadTree(double x1, double y1, double x2, double y2) {
	TL = NULL;
	TR = NULL;
	BL = NULL;
	BR = NULL;
	node = NULL;
	PARENT = NULL;
	V_TL = Vector2(x1, y1);
	V_BR = Vector2(x2, y2);
}

QuadTree::QuadTree(Vector2 topLeft, Vector2 bottomRight) {
	TL = NULL;
	TR = NULL;
	BL = NULL;
	BR = NULL;
	node = NULL;
	PARENT = NULL;
	V_TL = topLeft;
	V_BR = bottomRight;
}


void QuadTree::insert(Sphere *sp) {
	if (!inQuad(sp->p)) {
		// Look up
		if (this->PARENT == NULL) {
			// Sphere cannot be placed anywhere
		}
		else if (this->PARENT != NULL) {
			this->PARENT->insert(sp);
		}
	}
	// Ensure quadtree is only of certain resolution
	if (fabs(this->V_TL.x - this->V_BR.x) <= CELL_EPSILON &&
		fabs(this->V_TL.y - this->V_BR.y) <= CELL_EPSILON) {
		if (node == NULL) {
			node = sp;
		}
		return;
	}
	// Insert Sphere into correct 
	Vector2 centre = ((this->V_TL + this->V_BR) / 2);
	bool y_hat = centre.y >= sp->p.y;
	bool x_hat = centre.x >= sp->p.x;
	if (x_hat && y_hat) {
		// Top right? depends on your axis lol
		if (this->TL == NULL) {
			TL = new QuadTree(this->V_TL, centre);
		}
		this->TL->insert(sp);
		this->TL->PARENT = this;
	}
	else if (x_hat && !y_hat) {
		if (this->BL == NULL) {
			BL = new QuadTree(this->V_TL.x, centre.y,
							  centre.x, this->V_BR.y);
		}
		this->BL->insert(sp);
		this->BL->PARENT = this;
	}
	else if (!x_hat && y_hat) {
		if (this->TR == NULL) {
			TR = new QuadTree(centre.x, this->V_TL.y,
							  this->V_BR.x, centre.y);
		}
		this->TR->insert(sp);
		this->TR->PARENT = this;
	}
	else if (x_hat && !y_hat) {
		if (this->BL == NULL) {
			BR = new QuadTree(centre, this->V_BR);
		}
		this->BR->insert(sp);
		this->BR->PARENT = this;
	}
}


Sphere* QuadTree::search(Vector2 v) {
	// If the vector is in bounds,
		// Check the branches inside current node
	// Otherwise check if parrent is NULL, and look up 
	if (!inQuad(v)) {
		if (this->PARENT == NULL) {
			return NULL;
		}
		else if (this->PARENT != NULL) {
			return this->PARENT->search(v);
		}
	}
	if (this->node != NULL) {
		return node;
	}
	Vector2 centre = ((this->V_TL + this->V_BR) / 2);
	bool y_hat = centre.y >= v.y;
	bool x_hat = centre.x >= v.x;

	if (x_hat && y_hat) {
		// Top right? depends on your axis lol
		if (this->TL == NULL) {
			return NULL;
		}
		return this->TL->search(v);
	}
	else if (x_hat && !y_hat) {
		if (this->BL == NULL) {
			return NULL;
		}
		return this->BL->search(v);
	}
	else if (!x_hat && y_hat) {
		if (this->TR == NULL) {
			return NULL;
		}
		return this->TR->search(v);
	}
	else if (x_hat && !y_hat) {
		if (this->BL == NULL) {
			return NULL;
		}
		return this->BL->search(v);
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
