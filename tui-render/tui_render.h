#ifndef TUI_RENDER
#define TUI_RENDER

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <ctype.h>

struct Renderer {
	int buf[20][80];	
	int rows, cols;
};

int renderer_init(struct Renderer *r, int rows, int cols);



void renderer_uninit(struct Renderer *r);

#endif
