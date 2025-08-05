#ifndef COFFIN
#define COFFIN
typedef struct Coffin {
	Oneiro *corpse;
	Form *base;
	Form *side;
	int size[2];
} Coffin;

Coffin *makeCoffin(Oneiro *oni);
void placeCoffin(Coffin *cof);
void freeCoffin(Coffin *cof);
#endif
