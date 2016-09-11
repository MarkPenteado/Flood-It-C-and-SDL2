#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

struct window {
	SDL_Window* sdl_window;
	char* title;  // the title of the window, in UTF-8 encoding
	int x;        // the x position of the window
	int y;        // the y position of the window
	int width;    // the width of the window, in screen coordinates
	int height;   // the height of the window, in screen coordinates
	Uint32 flags; // fullscreen window, window can be resized, window is maximized, etc
};

typedef struct window window;

window* createWindow(char* title, int x, int y, int width, int height, Uint32 flags);
void destroyWindow(window** window);

#endif // WINDOW_H