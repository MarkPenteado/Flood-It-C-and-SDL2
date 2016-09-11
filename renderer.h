#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "window.h"

struct renderer {
	window* window;             // the window where rendering is displayed
	SDL_Renderer* sdl_renderer; // a 2D rendering context for a window.
	int index;                  // the index of the rendering driver to initialize
	Uint32 flags;               // fullscreen window, window can be resized, window is maximized, etc
};

typedef struct renderer renderer;

renderer* createRenderer(window** window, int index, Uint32 flags);
void renderClear(renderer** renderer);
void renderPresent(renderer** renderer);
int setRenderDrawColor(renderer** renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void destroyRenderer(renderer** renderer);

#endif // RENDERER_H