#ifndef PACMAN_H
#define PACMAN_H

#include "base/common.h"

class Game;

class Pacman{
public:
	Pacman(Game *game, vec2i pos):dir(0), game(game), pos(pos), timer(0){}

	void input(int in);

	void update();
	void render();

	vec2i getPos(){return pos;}
private:
	Game *game;

	vec2i pos;

	uint8_t dir; //0=LEFT; 1=UP; 2=RIGHT; 3=DOWN

	uint32_t timer;
};

#endif
