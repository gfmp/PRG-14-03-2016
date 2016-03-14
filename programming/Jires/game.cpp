#include "game.h"

char EndMessage[][60] = {
	"Vyhral jsi!",
	"Prohrál jsi!",
};

void Game::prepare(){
	uint32_t y,x;

	gameEnd = 0;
	paused = 0;
	imune = 0;

	score = 0;

	if(!random){
		SY=9;
		SX=29;
	}

	field = (uint32_t **) malloc(sizeof(uint32_t *) * SY);

	for(y=0;y<SY;++y){
		field[y] = (uint32_t*) malloc(sizeof(uint32_t) * SX);
	}

	for(y=0;y<SY;++y){
		for(x=0;x<SX;++x){
			if(!y || !x || y==SY-1 || x==SX-1){
				field[y][x] = 1;
			}else{
				field[y][x] = 2;
			}
		}
	}

	if(!random){
		for(x=2;x<=13;++x){
			field[2][x]=1;
			field[SY-3][x]=1;
		}
		for(++x;x<=26;++x){
			field[2][x]=1;
			field[SY-3][x]=1;
		}

		for(x=0;x<SX;++x){
			if(x!=7 && x!= 21)field[4][x]=1;
		}
		field[1][SX-2] = 3;
	}else{
		generateField();
	}

	pacman = new Pacman(this, vec2i(1, 1));	

	ghosts.push_back(new Ghost(this, vec2i(SX-2, SY-2), 2));
	ghosts.push_back(new Ghost(this, vec2i(1, SY-2), 3));
}

void Game::postare(){
	uint32_t i, y;

	for(y=0;y<SY;++y){
		free(field[y]);
	}
	free(field);

	delete pacman;
	for(i=0;i<ghosts.size();++i){
		delete ghosts[i];
	}
	ghosts.clear();
}

void Game::generateField(){
	uint32_t i;
	uint32_t SZ =SY*SX;
	for(i=0;i<sqrt(SZ)*SX/25;++i){
		uint32_t x = getRandInt(2, SX-3);
		uint32_t y = getRandInt(2, SY-3);

		generateWall(x,y, getRandInt(4), getRandInt((uint32_t)sqrt(SZ)/4)+1);
	}
	for(i=0;i<sqrt(SZ)/4;++i){
		uint32_t x = getRandInt(2, SX-3);
		uint32_t y = getRandInt(2, SY-3);
		if(field[y][x]==2)field[y][x]=3;
	}
}

int a=0;
void Game::generateWall(uint32_t x, uint32_t y, uint32_t dir, uint32_t len){
	uint32_t i;
	field[y][x]=1;
	refresh();
	for(i=1;i<len;++i){
		if(dir==0){
			if(field[y][x-i]==1)break;
			field[y][x-i]=1;
		}else if(dir==1){
			if(field[y-i][x]==1)break;
			field[y-i][x]=1;
		}else if(dir==2){
			if(field[y][x+i]==1)break;
			field[y][x+i]=1;
		}else{
			if(field[y+i][x]==1)break;
			field[y+i][x]=1;
		}
	}
}

void Game::run(){
	int in;

	uint32_t ticks = 0, renders = 0;
	double second, notTicked = 0, lastTime = glfwGetTime(), temp;
	uint8_t ticked = 0;
	while((in = getch())!=27){
		temp=glfwGetTime();
		notTicked += temp - lastTime;
		second += temp - lastTime;
		lastTime = temp;

		if(in!=ERR){
			pacman->input(in);
			if(in=='p'){
				paused=!paused;
			}
		}

		if(!gameEnd){
			while(notTicked > 1.0f/TPS){
				if(!paused)update();

				notTicked -= 1.0f/TPS;
				ticked = 1;
				ticks++;
			}
			if(ticked){
				ticked = 0;
				render();
				renders++;
			}
			

			if(second > 1.0f){
				this->ticks = ticks;
				this->renders = renders;
				renders = 0;
				ticks = 0;
				second-=1.0f;
			}

		}else{
			mvprintw(SY+2, 0, "%s", EndMessage[gameEnd-1]);
			mvprintw(SY+3, 0, "Stiskni ESC pro opusteni hry!");
			refresh();
		}

		usleep(1000);
	}
}

void Game::update(){
	uint32_t i, y, x;
	pacman->update();

	vec2i pos = pacman->getPos();
	if(field[pos.getY()][pos.getX()]==2){
		field[pos.getY()][pos.getX()]=0;
		score+=10;
	}else if(field[pos.getY()][pos.getX()]==3){
		field[pos.getY()][pos.getX()]=0;
		score+=50;
		imune=500;
	}

	ghosts[0]->AI(pacman->getPos());
	ghosts[1]->AI(pacman->getPos()+(pacman->getPos()-ghosts[0]->getPos()));

	for(i=0;i<ghosts.size();++i){
		if(ghosts[i]->getPos() == pacman->getPos()){
			if(imune){
				ghosts[i]->respawn();
				score+=100;
			}else gameEnd=2;
		}
		ghosts[i]->update();
		if(ghosts[i]->getPos() == pacman->getPos()){
			if(imune){
				ghosts[i]->respawn();
				score+=100;
			}else gameEnd=2;
		}
	}

	bool fruit = 0;
	for(y=0;y<SY && !fruit;++y){
		for(x=0;x<SX;++x){
			if(field[y][x]==2){
				fruit=1;
				break;
			}
		}
	}
	if(!fruit){
		gameEnd=1;
	}
	if(imune)imune--;
}

void Game::render(){
	uint32_t y, x, i;
	clear();

	for(y=0;y<SY;++y){
		for(x=0;x<SX;++x){
			if(field[y][x]==1)mvaddnwstr(y+OFFSETY,x+OFFSETX, L"░", 1);
			else if(field[y][x]==2){
				if(colors)attron(COLOR_PAIR(1));
				mvaddnwstr(y+OFFSETY,x+OFFSETX, L".", 1);
				if(colors)attroff(COLOR_PAIR(1));
			}else if(field[y][x]==3){
				if(colors)attron(COLOR_PAIR(2));
				mvaddnwstr(y+OFFSETY,x+OFFSETX, L"o", 1);
				if(colors)attroff(COLOR_PAIR(2));
			}
		}
	}
	if(colors)attron(COLOR_PAIR(imune?2:1));
	pacman->render();
	if(colors)attroff(COLOR_PAIR(imune?2:1));

	for(i=0;i<ghosts.size();++i){
		ghosts[i]->render();
	}

	mvprintw(SY+1, 0, "score: %d", score);
	if(paused)mvprintw(SY+2, 0, "Hra pozastavena!");
	mvprintw(SY+3, 0, "Ticks : %d, FPS : %d\n", ticks, renders);
	refresh();
}

uint8_t Game::ENTER(){
	curs_set(0);

	if(colors)colorsOn();
	else colorsOff();

	clear();

	prepare();
	run();
	postare();

	curs_set(1);

	return 1;
}
