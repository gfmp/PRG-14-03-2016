OUTPUT:= run

FILES:= main.cpp base/common.c base/menu.cpp myMenu.cpp game.cpp pacman.cpp ghost.cpp
OBJS:= main.o common.o menu.o myMenu.o game.o pacman.o ghost.o
GPPFLAGS=-std=c++11 -lncursesw -lglfw

all:

	g++ -c $(FILES) $(GPPFLAGS)
	g++ -o $(OUTPUT) $(OBJS) $(GPPFLAGS)
	
clean:
	rm -f run *.o
