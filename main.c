#include "FormNetwork.h"
int world = 50;
int frame = 50;
#include "oneiro.c"

void game();
void exitLoop(void *p, float val);
int main(int argc, char **argv) {
	initFormGlfw();
	Player *GM = makePlayer(0, 0, 0);
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
	placeForm(world/2, world/2, oni->self);

	FormLoop(game);

	for (int x = 0; x < world; x++) {
		for (int y = 0; y < world; y++) {
			removeFormPos(grass, x, y);
		}
	}
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

