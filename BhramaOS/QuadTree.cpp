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
	CENT = (V_TL + V_BR) / 2;
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
	CENT = (V_TL + V_BR) / 2;
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
	if (fabs(this->V_TL.x - this->V_BR.x) <= sim_consts::CELL_EPSILON &&
		fabs(this->V_TL.y - this->V_BR.y) <= sim_consts::CELL_EPSILON) {
		if (node == NULL) {
			node = sp;
		}
		return;
	}
	// Insert Sphere into correct 
	bool y_hat = this->CENT.y >= sp->p.y;
	bool x_hat = this->CENT.x >= sp->p.x;
	if (y_hat && x_hat) {
		// Top right? depends on your axis lol
		if (this->TL == NULL) {
			TL = new QuadTree(this->V_TL, this->CENT);
		}
		this->TL->insert(sp);
		this->TL->PARENT = this;
		this->TL->level = this->level + 1;
	}
	else if (!y_hat && x_hat) {
		if (this->BL == NULL) {
			BL = new QuadTree(this->V_TL.x, this->CENT.y,
							  this->CENT.x, this->V_BR.y);
		}
		this->BL->insert(sp);
		this->BL->PARENT = this;
		this->BL->level = this->level + 1;
	}
	else if (y_hat && !x_hat) {
		if (this->TR == NULL) {
			TR = new QuadTree(this->CENT.x, this->V_TL.y,
							  this->V_BR.x, this->CENT.y);
		}
		this->TR->insert(sp);
		this->TR->PARENT = this;
		this->TR->level = this->level + 1;
	}
	else if (!y_hat && x_hat) {
		if (this->BL == NULL) {
			BR = new QuadTree(this->CENT, this->V_BR);
		}
		this->BR->insert(sp);
		this->BR->PARENT = this;
		this->BR->level = this->level + 1;
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
	bool y_hat = this->CENT.y >= v.y;
	bool x_hat = this->CENT.x >= v.x;

	if (y_hat && x_hat) {
		// Top right? depends on your axis lol
		if (this->TL == NULL) {
			return NULL;
		}
		return this->TL->search(v);
	}
	else if (!y_hat && x_hat) {
		if (this->BL == NULL) {
			return NULL;
		}
		return this->BL->search(v);
	}
	else if (y_hat && !x_hat) {
		if (this->TR == NULL) {
			return NULL;
		}
		return this->TR->search(v);
	}
	else if (!y_hat && x_hat) {
		if (this->BL == NULL) {
			return NULL;
		}
		return this->BL->search(v);
	}
}


void QuadTree::move(Sphere *sp) {
	if (!inQuad(sp->p)) {
		// Insert on PARENT node
		this->PARENT->insert(sp);
		// Dereference Quad from PARENT node
		this->PARENT->remove(this);
	}
}


// This is only a method that a child node should invocate on a parent node. Otherwise this is an expensive operation.
// This will also have the unintended? side affect of deleting all if it's children nodes.
int QuadTree::remove(QuadTree *q) {
	bool y_hat = this->CENT.y >= q->CENT.y;
	bool x_hat = this->CENT.x >= q->CENT.x;

	if (y_hat && x_hat) {
		// Top right? depends on your axis lol
		if (*this->TL == *q) {
			delete q;
			return 1;
		}
		else if (this->TL != NULL) {
			this->TL->remove(q);
		}
	}
	else if (!y_hat && x_hat) {
		if (this->BL == NULL) {
			delete q;
			return 1;
		}
		else if (this->BL != NULL) {
			this->BL->remove(q);
		}
	}
	else if (y_hat && !x_hat) {
		if (this->TR == NULL) {
			delete q;
			return 1;
		}
		else if (this->TR != NULL) {
			this->TR->remove(q);
		}
	}
	else if (!y_hat && x_hat) {
		if (this->BR == NULL) {
			delete q;
			return 1;
		}
		else if (this->BR != NULL) {
			this->BR->remove(q);
		}
	}

	return -1;
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
}
