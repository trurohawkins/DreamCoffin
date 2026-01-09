#ifndef ONEIRO
#define ONEIRO

typedef struct Oneiro {
	Form *self;
	float moveDir[2];
	float destDir[2];
	int moveInterval;
	int moveCounter;
	intList *driftInput;
	intList *zipInput;
	int zip[2];
	int corners[8];
	float curAccel;
} Oneiro;

Oneiro *birthOneiro();

bool moveOneiro(Oneiro *oni);
int oneiroAction(Form *o, Action *a);

void setDrift(Oneiro *oni, int dir, bool on);
void setZip(Oneiro *oni, int corner, bool on);
void setDriftDirection(Oneiro *oni);
void setZipDirection(Oneiro *oni);
void setDestDir(Oneiro *oni, float x, float y);

void setCorners(Oneiro *oni, int *corners);

void driftX(void *o, float val);
void driftY(void *o, float val);
void driftUp(void *o, float val);
void driftLeft(void *o, float val);
void driftDown(void *o, float val);
void driftRight(void *o, float val);
void zipNW(void *o, float val);
void zipSW(void *o, float val);
void zipSE(void *o, float val);
void zipNE(void *o, float val);
#endif
