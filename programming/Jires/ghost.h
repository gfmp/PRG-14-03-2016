#ifndef GHOST_H
#define GHOST_H

#include "base/common.h"

class Game;

class Ghost{
public:
	Ghost(Game *game, vec2i pos, uint32_t col);
	~Ghost();

	void update();
	void render();

	void respawn(){pos = origPos;}

	void AI(vec2i goal);

	vec2i getPos(){return pos;}
private:
	bool AIspread(uint32_t i);

	uint32_t **AIfield;

	Game *game;

	vec2i pos;
	uint8_t dir;

	uint32_t timer;

	uint32_t col;

	vec2i origPos;
};

#endif
