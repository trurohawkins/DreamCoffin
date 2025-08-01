#ifndef ONEIRO
#define ONEIRO

typedef struct Oneiro {
	Form *self;
	int driftInterval;
	int driftCounter;
	bool mInput[4];
	intList *input;
	int move;
} Oneiro;

Oneiro *birthOneiro();

bool driftOneiro(Oneiro *oni, int dir);
int oneiroAction(Form *o, Action *a);

void driftUp(void *o, float val);
void driftLeft(void *o, float val);
void driftDown(void *o, float val);
void driftRight(void *o, float val);
#endif
