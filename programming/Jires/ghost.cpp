#include "ghost.h"
#include "game.h"

Ghost::Ghost(Game *game, vec2i pos, uint32_t col):dir(0), game(game), pos(pos), origPos(pos), timer(0), col(col){
	uint32_t y,x;
	AIfield = (uint32_t **) malloc(sizeof(uint32_t *) * game->SY);

	for(y=0;y<game->SY;++y){
		AIfield[y] = (uint32_t*) malloc(sizeof(uint32_t *) * game->SX);
	}
}

Ghost::~Ghost(){
	uint32_t y,x;
	for(y=0;y<game->SY;++y){
		free(AIfield[y]);
	}
	free(AIfield);
}

void Ghost::update(){
	timer++;
	if(timer>=GHOST_TIMER){
		if(dir==0){
			if(game->getField()[pos.getY()][pos.getX()-1]!=1){
				pos[0]--;
			}
		}else if(dir==1){
			if(game->getField()[pos.getY()-1][pos.getX()]!=1){
				pos[1]--;
			}
		}else if(dir==2){
			if(game->getField()[pos.getY()][pos.getX()+1]!=1){
				pos[0]++;
			}
		}else{
			if(game->getField()[pos.getY()+1][pos.getX()]!=1){
				pos[1]++;
			}
		}
		timer = 0;
	}
}

void Ghost::render(){
	if(colors)attron(COLOR_PAIR(col));
	mvaddnwstr(pos.getY()+OFFSETY, pos.getX()+OFFSETX, L"ᗣ", 1);
	if(colors)attroff(COLOR_PAIR(col));
}

bool Ghost::AIspread(uint32_t i){
	uint32_t y,x;
	uint32_t SY = game->SY, SX = game->SX;

	bool ret = 0;
	for(y=0;y<SY;++y){
		for(x=0;x<SX;++x){
			if(AIfield[y][x]==i){
				if(AIfield[y][x-1] && AIfield[y][x-1] > i){
					AIfield[y][x-1] = i+1;
					ret = 1;
				}
				if(AIfield[y-1][x] && AIfield[y-1][x] > i){
					AIfield[y-1][x] = i+1;
					ret = 1;
				}
				if(AIfield[y][x+1] && AIfield[y][x+1] > i){
					AIfield[y][x+1] = i+1;
					ret = 1;
				}
				if(AIfield[y+1][x] && AIfield[y+1][x] > i){
					AIfield[y+1][x] = i+1;
					ret = 1;
				}
			}
		}
	}
	return ret;
}

void Ghost::AI(vec2i goal){
	uint32_t y,x,i;
	uint32_t SY = game->SY, SX = game->SX;

	if(goal.getX()<1)goal.setX(1);
	if(goal.getY()<1)goal.setY(1);
	if(goal.getX()>SX-2)goal.setX(SX-2);
	if(goal.getY()>SY-2)goal.setY(SY-2);

	for(y=0;y<SY;++y){
		for(x=0;x<SX;++x){
			if(game->getField()[y][x]==1)AIfield[y][x]=0;
			else AIfield[y][x] = -1;
		}
	}

	AIfield[goal.getY()][goal.getX()] = 1;

	for(i=1;AIspread(i);++i){
		if(AIfield[pos.getY()][pos.getX()] && AIfield[pos.getY()][pos.getX()]!=-1){
			if(AIfield[pos.getY()][pos.getX()-1] && AIfield[pos.getY()][pos.getX()-1]!=-1){
				dir=0;
			}else if(AIfield[pos.getY()-1][pos.getX()] && AIfield[pos.getY()-1][pos.getX()]!=-1){
				dir=1;
			}else if(AIfield[pos.getY()][pos.getX()+1] && AIfield[pos.getY()][pos.getX()+1]!=-1){
				dir=2;
			}else if(AIfield[pos.getY()+1][pos.getX()] && AIfield[pos.getY()+1][pos.getX()]!=-1){
				dir=3;
			}
			break;
		}
	}
}
