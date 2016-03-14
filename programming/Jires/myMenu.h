#ifndef MYMENU_H
#define MYMENU_H
#include "base/common.h"
#include "base/menu.h"

class menuHandler{
public:
	menuHandler(){};
	~menuHandler(){};

	virtual uint8_t ENTER(){return 0;};
};

class myMenu:public menu{
public:
	myMenu():handler(0){};
	~myMenu(){};

	void setHandler(menuHandler *handler){this->handler=handler;};
	void run();
private:
	menuHandler *handler;
};

#endif
