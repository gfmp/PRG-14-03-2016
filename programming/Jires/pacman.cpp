#include "pacman.h"
#include "game.h"

void Pacman::update(){
	timer++;
	if(timer>=PACMAN_TIMER){
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


void Pacman::input(int in){
	if(in == KEY_LEFT){
		if(game->getField()[pos.getY()][pos.getX()-1]!=1){
			dir = 0;
		}
	}else if(in == KEY_UP){
		if(game->getField()[pos.getY()-1][pos.getX()]!=1){
			dir = 1;
		}
	}else if(in == KEY_RIGHT){
		if(game->getField()[pos.getY()][pos.getX()+1]!=1){
			dir = 2;
		}
	}else if(in == KEY_DOWN){
		if(game->getField()[pos.getY()+1][pos.getX()]!=1){
			dir = 3;
		}
	}
}

void Pacman::render(){
	if(dir == 0){
		mvaddnwstr(pos.getY()+OFFSETY, pos.getX()+OFFSETX, L"ᗤ", 1);
	}else if(dir == 1){
		mvaddnwstr(pos.getY()+OFFSETY, pos.getX()+OFFSETX, L"U", 1);
	}else if(dir == 2){
		mvaddnwstr(pos.getY()+OFFSETY, pos.getX()+OFFSETX, L"ᗧ", 1);
	}else{
		mvaddnwstr(pos.getY()+OFFSETY, pos.getX()+OFFSETX, L"A", 1);
	}
}
