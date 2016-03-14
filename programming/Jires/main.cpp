#include "base/common.h"
#include "game.h"
#include "myMenu.h"

void initColors(){
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
}

void runInit(){
	Game *handler = new Game();

	myMenu *men = new myMenu();

	men->addLine(new intLn(0,0, 15,(char*)"Vyska:", &(handler->SY), (char*)"9"));
	men->addLine(new intLn(1,0, 15,(char*)"Sirka:", &(handler->SX), (char*)"29"));
	men->addLine(new boolLn(2,0, 15,(char*)"Nahodny svet:", (uint8_t*)&(handler->random)));
	men->addLine(new boolLn(3,0, 15,(char*)"Barvy:", (uint8_t*)&(colors)));

	men->addLine(new menuLn(4,0,(char*)" "));
	men->addLine(new menuLn(5,0,(char*)"ENTER pro spusteni hry!\n"));

	men->setHandler(handler);

	men->run();

	delete men;
}

int main(){

	int input;

	srand(time(NULL));

	setlocale(LC_CTYPE, "cs_CZ.UTF-8");

	glfwInit();

	initW();
	if(colorsAble)initColors();
	getmaxyx(stdscr, maxY, maxX);

	runInit();

	endW();

	return 0;
}
