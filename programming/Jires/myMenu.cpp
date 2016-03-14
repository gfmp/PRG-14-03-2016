#include "myMenu.h"

void myMenu::run(){
	int in;
	uint32_t choose=0;

	resetPrint();

	lines[choose]->setcursor();

	while((in = getch())!=27){
		if(in!=ERR){
			if(in == KEY_UP && choose)lines[--choose]->setcursor();
			else if(in == KEY_DOWN && choose<lines.size()-1)lines[++choose]->setcursor();
			else if((in == KEY_ENTER || in == '\n' || in == '\r') && handler){
				escRun();
				if(handler->ENTER()){
					resetPrint();
					lines[choose]->setcursor();
				}
				lines[choose]->setcursor();
			}
			else lines[choose]->update(in);
		}
		refresh();
		usleep(1000);
	}

	escRun();
}
