#ifndef GAME_H
#define GAME_H

#include "base/common.h"
#include "myMenu.h"
#include "pacman.h"
#include "ghost.h"

class Game: public menuHandler{
public:
	Game():random(0){}

	uint8_t ENTER();

	uint32_t SX,SY;
	bool random;

	uint32_t **getField(){return field;}
private:
	void generateField();
	void generateWall(uint32_t x, uint32_t y, uint32_t dir, uint32_t len);

	uint32_t gameEnd, paused;

	vector<Ghost *> ghosts;

	void prepare();
	void postare();

	void run();
	void update();
	void render();

	uint8_t testData();

	uint32_t **field;

	Pacman *pacman;

	uint32_t score;

	uint32_t imune;

	uint32_t ticks, renders;
};

#endif
