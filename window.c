#include "window.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createChar(char* str) {
	char* newChar = (char*)malloc(sizeof(char) * strlen(str));
	if(newChar == NULL) {
		printf("newChar could not be created!\n");
		return NULL;
	}
	strcpy(newChar, str);
	return newChar;
}

window* createWindow(char* title, int x, int y, int width, int height, Uint32 flags) {
	window* newWindow = (window*)malloc(sizeof(window));
	if(newWindow == NULL) {
		printf("newWindow could not be created!\n");
		return NULL;
	}
	newWindow->title = createChar(title);
	newWindow->x = x;
	newWindow->y = y;
	newWindow->width = width;
	newWindow->height = height;
	newWindow->flags = flags;
	newWindow->sdl_window = SDL_CreateWindow(newWindow->title, newWindow->x, newWindow->y, 
		newWindow->width, newWindow->height, newWindow->flags);
	if(newWindow->sdl_window == NULL) {
		printf("newWindow->sdl_window could not be created! SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}
	return newWindow;
}

void destroyWindow(window **window) {
	if(*window != NULL) {
		SDL_DestroyWindow((*window)->sdl_window);
		(*window)->sdl_window = NULL;
		free(*window);
		*window = NULL;
	}
}