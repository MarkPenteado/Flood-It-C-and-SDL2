#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL.h>
#include "window.h"
#include "renderer.h"

struct core {
	window* window;
	renderer *renderer;
};

typedef struct core core;

core* createCore(window** window, renderer** renderer);
void start(core** core);
void update(core** core);
void destroyCore(core** core);

#endif // CORE_H