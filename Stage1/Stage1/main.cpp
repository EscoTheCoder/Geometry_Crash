#include "sgg/graphics.h"
#include <iostream>
#include <stdio.h>
#include "util.h"
#include <string>
#include "GameState.h"

using namespace std;


void draw() {
	GameState::getInstance()->draw();
}

void update(float dt) {
	GameState::getInstance()->update(dt);
}

void init() {
	GameState::getInstance()->init();
}


int main(int argc, char** argv) {

	graphics::createWindow(800, 800, "Geometry Crash Platformer");

	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getInstance()->getCanvasDimensions().first,
		GameState::getInstance()->getCanvasDimensions().second);

	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	//graphics::setFullScreen(true);

	graphics::startMessageLoop();



	return 0;
}