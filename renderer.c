#include "renderer.h"
#include <stdio.h>
#include <stdlib.h>

renderer* createRenderer(window** window, int index, Uint32 flags) {
	renderer* newRenderer = (renderer*)malloc(sizeof(renderer));
	if(newRenderer == NULL) {
		printf("newRenderer could not be created!\n");
		return NULL;
	}
	newRenderer->window = *window;
	newRenderer->index = index;
	newRenderer->flags = flags;
	newRenderer->sdl_renderer = SDL_CreateRenderer(newRenderer->window->sdl_window, 
		newRenderer->index, newRenderer->flags);
	if(newRenderer == NULL) {
		printf("newRenderer->renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}
	return newRenderer;
}

void renderClear(renderer** renderer) {
	SDL_RenderClear((*renderer)->sdl_renderer);
}

void renderPresent(renderer** renderer) {
	SDL_RenderPresent((*renderer)->sdl_renderer);
}

int setRenderDrawColor(renderer** renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return SDL_SetRenderDrawColor((*renderer)->sdl_renderer, r, g, b, a);
}

void destroyRenderer(renderer** renderer) {
	if(*renderer != NULL) {
		SDL_DestroyRenderer((*renderer)->sdl_renderer);
		(*renderer)->sdl_renderer = NULL;
		free(*renderer);
		*renderer = NULL;
	}
}