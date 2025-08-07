#include "coffin.h"

Coffin *makeCoffin(Oneiro *oni) {
	Coffin *cof = calloc(1, sizeof(Coffin));
	cof->size[0] = 41;
	cof->size[1] = 31;
	cof->base = makeForm(0, 0, 0, cof->size[0], cof->size[1]);
	cof->side = makeForm(1, 1, 1, 0, 0);
	cof->side->id = 1;
	cof->corpse = oni;
	placeCoffin(cof);
	placeForm(world/2, world/2, oni->self);

	return cof;
}

void placeCoffin(Coffin *cof) {
	placeForm(world/2, world/2, cof->base);
	int xPos = world/2 - cof->size[0]/2;
	int yPos = world/2 - cof->size[1]/2;
	for (int x = 0; x < cof->size[0]; x++) {
		for (int y = 0; y < cof->size[1]; y++) {
			if (x == 0 || y == 0 || x == cof->size[0]-1 || y == cof->size[1]-1) {
				placeForm(xPos+x, yPos+y, cof->side);
			}
		}
	}
	int corners[8] = {xPos+1, yPos + cof->size[1]-2,  xPos+1, yPos+1,  xPos + cof->size[0]-2, yPos+1,  xPos + cof->size[0]-2, yPos + cof->size[1]-2};
	setCorners(cof->corpse, corners);
}

void freeCoffin(Coffin *cof) {
	removeForm(cof->base);
	int xPos = world/2 - cof->size[0]/2;
	int yPos = world/2 - cof->size[1]/2;
	for (int x = 0; x < cof->size[0]; x++) {
		for (int y = 0; y < cof->size[1]; y++) {
			if (x == 0 || y == 0 || x == cof->size[0]-1 || y == cof->size[1]-1) {
				removeFormPos(cof->side, xPos+x, yPos+y);
			}
		}
	}

	deleteForm(cof->base);
	deleteForm(cof->side);
	free(cof);
}
