#ifndef MENU_H
#define MENU_H
#include "common.h"

static char boolS[2][4] = {"OFF", "ON "};

class menuLn{
public:
	menuLn(uint32_t yP, uint32_t xP, char *str): yP(yP), xP(xP), str(str){};
	virtual ~menuLn(){};

	virtual void resetprint();
	virtual void setcursor();
	virtual void update( int in){};
	virtual void save(){};
protected:
	uint32_t yP,xP;
	char *str;
};

class intLn: public menuLn{
public:
	intLn(uint32_t yP, uint32_t xP, uint32_t dataXP, char *str, uint32_t *out, char *initTemp=0);
	~intLn(){};

	void resetprint();
	void setcursor();
	void update(int in);
	void save();
private:
	uint32_t *out;
	char temp[10];
	uint32_t tempLen, dataXP;
};
class strLn: public menuLn{
public:
	strLn(uint32_t yP, uint32_t xP, uint32_t dataXP, char *str, char *out, uint32_t maxSZ, char *initTemp=0);
	~strLn(){};

	void resetprint();
	void setcursor();
	void update(int in);
	void save();
private:
	char *out;
	char temp[80];
	uint32_t tempLen, dataXP;
	uint32_t maxSZ;
};
class boolLn: public menuLn{
public:
	boolLn(uint32_t yP, uint32_t xP, uint32_t dataXP, char *str, uint8_t *out);
	~boolLn(){};

	void resetprint();
	void setcursor();
	void update(int in);
	void save();
private:
	uint8_t *out, temp;
	uint32_t dataXP;
};

class menu{
public:
	menu(){};
	virtual ~menu();

	void addLine(menuLn*);

	void resetPrint();
	virtual void run(){};
	void escRun();

protected:
	vector<menuLn*> lines;
};

#endif
