#include "common.h"

uint32_t maxX=40;
uint32_t maxY=25;

uint8_t colors;
uint8_t colorsAble;

void initW(){
	initscr();

	if(has_colors()){
		start_color();

		colors = 1;
		colorsAble = 1;
	}else{
		colors = 0;
		colorsAble = 0;
	}
	
	noecho();
	raw();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
}

void endW(){
	endwin();
}
