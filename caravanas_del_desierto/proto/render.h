#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

struct Renderer {
	int buf[24][80];	
	int x,y;
};

void renderer_init(struct Renderer *render);
int renderer_copy(struct Renderer *render, const char *linebuf, int x, int y, int r_flags);
int renderer_draw(const struct Renderer *render);
int render_clear(struct Renderer *render);

#endif
