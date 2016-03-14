#include "menu.h"

void menuLn::resetprint(){
	mvprintw(yP, xP, "%s", str);
}
void menuLn::setcursor(){
	move(yP, xP);
}

intLn::intLn(uint32_t yP, uint32_t xP, uint32_t dataXP, char *str, uint32_t *out, char *initTemp):menuLn(yP, xP, str), out(out), dataXP(dataXP){
	char *mem=temp;
	if(initTemp && (tempLen = strlen(initTemp)) <= 9){
		while(*initTemp){
			if(*initTemp >= '0' && *initTemp <= '9')*mem++ = *initTemp++;
			else{
				temp[tempLen=0]=0;
				break;
			}
		}
	}else temp[tempLen=0]=0;
}

void intLn::resetprint(){
	mvprintw(yP, xP, "%s", str);
	mvprintw(yP, xP+dataXP, "%s", temp);
}
void intLn::setcursor(){
	move(yP, xP+dataXP+tempLen);
}

void intLn::update(int in){
	if(in>='0' && in<= '9' && tempLen<9){
		mvaddch(yP, xP+tempLen+dataXP,in);
		temp[tempLen++]=in;
	}
	else if((in == KEY_BACKSPACE || in == 8 || in == 10) && tempLen){
		temp[--tempLen]=0;
		mvaddch(yP, xP+tempLen+dataXP, ' ');
		move(yP, xP+tempLen+dataXP);
	}
}

void intLn::save(){
	*out = atoi(temp);
}


strLn::strLn(uint32_t yP, uint32_t xP, uint32_t dataXP, char *str, char *out, uint32_t maxSZ, char *initTemp):menuLn(yP, xP, str), out(out), dataXP(dataXP), maxSZ(maxSZ){
	char *mem=temp;
	if(initTemp && (tempLen = strlen(initTemp)) <= 79){
		while(*initTemp){
			if(*initTemp >= ' ' && *initTemp <= '~')*mem++ = *initTemp++;
			else{
				temp[tempLen=0]=0;
				break;
			}
		}
	}else temp[tempLen=0]=0;
}

void strLn::resetprint(){
	mvprintw(yP, xP, "%s", str);
	mvprintw(yP, xP+dataXP, "%s", temp);
}
void strLn::setcursor(){
	move(yP, xP+dataXP+tempLen);
}

void strLn::update(int in){
	if(in>=' ' && in<= '~' && tempLen<79 && tempLen < maxSZ-1){
		mvaddch(yP, xP+tempLen+dataXP,in);
		temp[tempLen++]=in;
	}
	else if((in == KEY_BACKSPACE || in == 8) && tempLen){
		temp[--tempLen]=0;
		mvaddch(yP, xP+tempLen+dataXP, ' ');
		move(yP, xP+tempLen+dataXP);
	}
}

void strLn::save(){
	strcpy(out, temp);
}


boolLn::boolLn(uint32_t yP, uint32_t xP, uint32_t dataXP, char *str, uint8_t *out):menuLn(yP, xP, str), out(out), dataXP(dataXP){
	temp = *out;
}

void boolLn::resetprint(){
	mvprintw(yP, xP, "%s", str);
	mvprintw(yP, xP+dataXP, "%s", boolS[temp]);
}
void boolLn::setcursor(){
	move(yP, xP+dataXP+3);
}

void boolLn::update(int in){
	if(in == KEY_LEFT)mvprintw(yP, xP+dataXP, boolS[temp=0]);
	else if(in == KEY_RIGHT)mvprintw(yP, xP+dataXP, boolS[temp=1]);
	move(yP, xP+dataXP+3);
}

void boolLn::save(){
	*out = temp;
}

menu::~menu(){
	uint32_t i;
	for(i=0;i<lines.size();++i){
		lines[i]->save();
	}
	lines.clear();
}

void menu::addLine(menuLn* line){
	lines.push_back(line);
}

void menu::resetPrint(){
	uint32_t i;

	clear();
	for(i=0;i<lines.size();++i){
		lines[i]->resetprint();
	}
}

void menu::escRun(){
	uint32_t i;

	for(i=0;i<lines.size();++i){
		lines[i]->save();
	}
}
