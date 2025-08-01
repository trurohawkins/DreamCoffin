#include "FormNetwork.h"
#include "oneiro.c"

void game();
void exitLoop(void *p, float val);
int world = 30;
int frame = 30;
int main(int argc, char **argv) {
	initFormGlfw();
	Player *GM = makePlayer(0, 0, 0);
	addPlayer(GM);
	addControl(GM, "K0!", exitLoop);

	setBackgroundColor(0.1, 0.5, 0.3, 1);
	createWorld(world, world, frame, frame);
	WorldView *wv = getDefaultView();
	setFrameMin(wv, frame);

	Oneiro *oni = birthOneiro();
	placeForm(world/2, world/2, oni->self);

	FormLoop(game);

	exitGame();
	free(oni);
}

void game() {
	actorListDo();
	drawWorldDebug(getWorld());
}

void exitLoop(void *p, float val) {
	if (val == 1) {
		stopLoop();
	}
}

