#ifndef	COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <locale.h>
#include <wchar.h>

#include <time.h>


#include <GLFW/glfw3.h>

#ifdef __unix__
//#include <ncurses.h>
#include <ncursesw/ncurses.h>
#else
#include "../winLib/curses.h"
#endif

#include "mathlib.h"

typedef Vector2i vec2i;
typedef Vector3i vec3i;
typedef Vector4i vec4i;

typedef Vector2f vec2;
typedef Vector3f vec3;
typedef Vector4f vec4;

typedef Vector2d vec2d;
typedef Vector3d vec3d;
typedef Vector4d vec4d;


typedef Matrix2i mat2i;
typedef Matrix3i mat3i;
typedef Matrix4i mat4i;

typedef Matrix2f mat2;
typedef Matrix3f mat3;
typedef Matrix4f mat4;

typedef Matrix2d mat2d;
typedef Matrix3d mat3d;
typedef Matrix4d mat4d;

typedef Quaternion quat;

using namespace std;

extern uint32_t maxX;
extern uint32_t maxY;

extern uint8_t colors;
extern uint8_t colorsAble;

inline void colorsOn(){assume_default_colors(COLOR_WHITE, COLOR_BLACK); colors=1;};
inline void colorsOff(){use_default_colors(); colors=0;};

inline uint32_t getRandInt(uint32_t n){return rand()%n;}
inline uint32_t getRandInt(uint32_t start, uint32_t end){return start+rand()%(end-start);}

void initW();
void endW();

#define OFFSETX 1
#define OFFSETY 1

#define TPS 50

#define PACMAN_TIMER 25
#define GHOST_TIMER 30

#endif
