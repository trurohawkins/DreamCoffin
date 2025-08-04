#include "oneiro.h"
int minSpeed = 20;

Oneiro *birthOneiro() {
	Oneiro *oneiro = calloc(1, sizeof(Oneiro));
	oneiro->moveInterval = 30;
	//oneiro->curAccel = 1;
	oneiro->zip[0] = -1;
	oneiro->zip[1] = -1;
	int c[8] = {0, world-1,  0, 0,  world-1, 0,  world-1, world-1};
	memcpy(oneiro->corners, c, sizeof(int) * 8);
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
	addControl(p, "K0O", zipNW);
	addControl(p, "K0K", zipSW);
	addControl(p, "K0L", zipSE);
	addControl(p, "K0P", zipNE);
	
	return oneiro;
}

float lerpDir(float cur, float dest, float accel) {
	if (cur > dest) {
		if (cur - accel > dest) {
			cur -= accel;
		} else {
			cur = dest;
		}
	} else if (cur < dest) {
		if (cur + accel < dest) {
			cur += accel;
		} else {
			cur = dest;
		}
	}
	return cur;
}

int oneiroAction(Form *o, Action *a) {
	Oneiro *oni = (Oneiro*)a->vars;

	if (oni->zip[0] < 0 && oni->zip[1] < 0) {
		setDriftDirection(oni);
	} else {
		setZipDirection(oni);
	}

	float mag = sqrt(oni->moveDir[0] * oni->moveDir[0] + oni->moveDir[1] * oni->moveDir[1]);
	if (mag != 0) {
		//printf("%.2f (%.2f, %.2f) -> (%.2f, %.2f) %.2f\n", oni->curAccel, oni->moveDir[0], oni->moveDir[1], oni->destDir[0], oni->destDir[1], mag);
	}
	if (oni->moveCounter < minSpeed - mag) {//oni->moveInterval) {
		oni->moveCounter++;	
	} else {
		if (oni->moveDir != oni->destDir) {
			//printf("-> %f, %f\n", oni->destDir[0], oni->destDir[1]);
			//oni->moveDir[0] = lerpDir(oni->moveDir[0], oni->destDir[0], oni->curAccel);
			//oni->moveDir[1] = lerpDir(oni->moveDir[1], oni->destDir[1], oni->curAccel);
			oni->moveDir[0] = lerp(oni->moveDir[0], oni->destDir[0], oni->curAccel);
			oni->moveDir[1] = lerp(oni->moveDir[1], oni->destDir[1], oni->curAccel);
			if (oni->curAccel + 0.1f < 1) {
				oni->curAccel += 0.1f;
			} else {
				oni->curAccel = 1;
			}
		}
		moveOneiro(oni);
		oni->moveCounter = 0;
	}
}

bool moveOneiro(Oneiro *oni) {
	if (oni->moveDir[0] != 0 || oni->moveDir[1] != 0) {
		int dest[2] = {oni->self->pos[0], oni->self->pos[1]};
		int d = abs(oni->moveDir[0]) > abs(oni->moveDir[1]) ? 0 : 1;
		//dest[d] += sign(oni->moveDir[d]);
		dest[0] += sign(oni->moveDir[0]);
		dest[1] += sign(oni->moveDir[1]);
		//printf("movei to %i, %i\n", dest[0], dest[1]);
		if (dest[0] > -1 && dest[1] > -1 && dest[0] < world && dest[1] < world) {
			removeForm(oni->self);
			placeForm(dest[0], dest[1], oni->self);
		}
	}
}

int getLast(intList *stack) {
	int lastInp = -1;
	intList *count = stack;//oni->driftInput;
	while (count) {
		lastInp = count->data;
		count = count->next;
	}
	return lastInp;
}

void setDrift(Oneiro *oni, int dir, bool on) {
	if (on) {
		if (addToIntListSingle(&oni->driftInput, dir)) {
			//oni->driftCounter = oni->driftInterval;
			//setDriftDirection(oni);
		}
	} else {
		//oni->mInput[dir] = false;
		removeFromIntList(&oni->driftInput, dir);
		//setDriftDirection(oni);
	}
}

void setDriftDirection(Oneiro *oni) {
		int lastInp = getLast(oni->driftInput);//-1;
		int *d = getDir4(lastInp);
		//oni->destDir[0] = d[0];// * 470;
		//oni->destDir[1] = d[1];// * 470;
		setDestDir(oni, d[0], d[1]);
}

void setZip(Oneiro *oni, int corner, bool on) {
	if (on) {
		addToIntListSingle(&oni->zipInput, corner);
		oni->zip[0] = oni->corners[corner];
		oni->zip[1] = oni->corners[corner+1];
	} else {
		removeFromIntList(&oni->zipInput, corner);
		int lastInp = getLast(oni->zipInput);//-1;
		if (lastInp < 0) {
			oni->zip[0] = -1;
			oni->zip[1] = -1;
		} else {
			oni->zip[0] = oni->corners[lastInp];
			oni->zip[1] = oni->corners[lastInp+1];
		}
	}
}

void setZipDirection(Oneiro *oni) {
	/*
	for (int i = 0; i < 2; i++) {
		oni->moveDir[i] = sign(oni->zip[i] - oni->self->pos[i]);
	}
	*/
	/*
	oni->destDir[0] = 0;
	oni->destDir[1] = 0;
	int d = abs(oni->self->pos[0] - oni->zip[0]) > abs(oni->self->pos[1] - oni->zip[1]) ? 0 : 1;
	oni->destDir[d] = sign(oni->zip[d] - oni->self->pos[d]) * minSpeed;
	*/
	float xd = sign(oni->zip[0] - oni->self->pos[0]);
	//printf("%f = %f -> %i\n", xd, oni->self->pos[0], oni->zip[0]);
	setDestDir(oni, sign(oni->zip[0] - oni->self->pos[0]) * minSpeed, sign(oni->zip[1] - oni->self->pos[1]) * minSpeed);
	/*
	if (abs(oni->self->pos[0] - oni->zip[0]) > abs(oni->self->pos[1] - oni->zip[1])) {
		setDestDir(oni, sign(oni->zip[0] - oni->self->pos[0]) * minSpeed, 0);
	} else {
		setDestDir(oni, 0, sign(oni->zip[1] - oni->self->pos[1]) * minSpeed);
	}
	*/
}

void setDestDir(Oneiro *oni , float x, float y) {
	if (oni->destDir[0] != x || oni->destDir[1] != y) {
		//printf("(%f, %f) -> (%f, %f)\n", oni->destDir[0], oni->destDir[1], x, y);
		oni->destDir[0] = x;
		oni->destDir[1] = y;
		if (abs(oni->destDir[0] - oni->moveDir[0]) <= 1 || abs(oni->destDir[1] - oni->moveDir[1]) <= 1 || abs(oni->destDir[0]) == 1 || abs(oni->destDir[1]) == 1) {
			oni->curAccel = 1;
		} else {
			oni->curAccel = 0;
		}
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

void zipNW(void *o, float val) {
	setZip(o, 0, val == 1);
}

void zipSW(void *o, float val) {
	setZip(o, 2, val == 1);
}

void zipSE(void *o, float val) {
	setZip(o, 4, val == 1);
}

void zipNE(void *o, float val) {
	setZip(o, 6, val == 1);
}

