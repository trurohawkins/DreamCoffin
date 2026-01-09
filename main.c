#include "FormNetwork.h"
int world = 51;
int frame = 51;
#include "oneiro.c"
#include "coffin.c"

void game();
void exitLoop(void *p, float val);
int main(int argc, char **argv) {
	initFormGlfw();
	Player *GM = makePlayer(0, 1, 0);
	addPlayer(GM);
	addControl(GM, "K0!", exitLoop);

	setBackgroundColor(0, 0, 0, 1);
	createWorld(world, world, frame, frame);
	WorldView *wv = getDefaultView();
	setFrameMin(wv, frame);

	Form *grass = makeForm(0.1, 0.5, 0.3, 0, 0);
	for (int x = 0; x < world; x++) {
		for (int y = 0; y < world; y++) {
			placeForm(x, y, grass);
		}
	}

	Oneiro *oni = birthOneiro();
	Coffin *cof = makeCoffin(oni);

	FormLoop(game);

	for (int x = 0; x < world; x++) {
		for (int y = 0; y < world; y++) {
			removeFormPos(grass, x, y);
		}
	}
	deleteForm(grass);
	freeCoffin(cof);
	exitGame();
	free(oni);
}

void game() {
	actorListDo();
	drawWorldDebug(getWorld());
	drawGrid();
}

void exitLoop(void *p, float val) {
	if (val == 1) {
		stopLoop();
	}
}

