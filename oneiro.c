#include "oneiro.h"

Oneiro *birthOneiro() {
	Oneiro *oneiro = malloc(sizeof(Oneiro));
	oneiro->driftInterval = 30;
	oneiro->driftCounter = 0;
	oneiro->move = -1;
	oneiro->input = 0;
	oneiro->self = makeForm(0.4, 0.1, 0.5, 1, 1);

	Actor *actor = makeActor(oneiro->self);
	Action *a = makeAction(oneiroAction, oneiro);
	addAction(actor, a);
	addActor(actor);

	Player *p = makePlayer(oneiro, 1, 0);
	addPlayer(p);
	addControl(p, "K0W", driftUp);
	addControl(p, "K0A", driftLeft);
	addControl(p, "K0S", driftDown);
	addControl(p, "K0D", driftRight);

	return oneiro;
}

int oneiroAction(Form *o, Action *a) {
	Oneiro *oni = (Oneiro*)a->vars;
	int lastInp = -1;
	intList *count = oni->input;
	while (count) {
		lastInp = count->data;
		count = count->next;
	}

	if (oni->driftCounter < oni->driftInterval) {
		oni->driftCounter++;	
	} else {
		oni->driftCounter = 0;
		driftOneiro(oni, lastInp);
	}
}

bool driftOneiro(Oneiro *oni, int dir) {
	if (dir > -1 && dir < 4) {
		removeForm(oni->self);
		int *d = getDir4(dir);
		oni->self->pos[0] += d[0];
		oni->self->pos[1] += d[1];
		placeForm(oni->self->pos[0], oni->self->pos[1], oni->self);
	}
}

void setDrift(Oneiro *oni, int dir, bool on) {
	if (on) {
		if (addToIntListSingle(&oni->input, dir)) {
			//oni->driftCounter = oni->driftInterval;
		}
	} else {
		//oni->mInput[dir] = false;
		removeFromIntList(&oni->input, dir);
	}
}

void driftUp(void *o, float val) {
	setDrift(o, 0, val == 1);
}

void driftLeft(void *o, float val) {
	setDrift(o, 1, val == 1);
}

void driftDown(void *o, float val) {
	setDrift(o, 2, val == 1);
}

void driftRight(void *o, float val) {
	setDrift(o, 3, val == 1);
}

