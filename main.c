#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "window.h"
#include "renderer.h"
#include "core.h"

int main(int argc, char **argv) {
	window* window = NULL;
	renderer* renderer = NULL;
	core* core = NULL;

	TTF_Init();
	if(SDL_Init(SDL_INIT_VIDEO) < 0) return -1; // init SDL2
	printf("Jogo inicializado!\n");
	window = createWindow("Jogo da Inundacao - MarkPenteado - 2016", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		800, 600, SDL_WINDOW_OPENGL);
	renderer = createRenderer(&window, -1, SDL_RENDERER_ACCELERATED);
	core = createCore(&window, &renderer);

	// main game logic
	start(&core);
    update(&core);

	// realease memory
	destroyCore(&core);
	destroyRenderer(&renderer);
	destroyWindow(&window);
	SDL_Quit(); // close SDL2
	TTF_Quit();
	printf("Jogo finalizado!\n");
	return 0;
}
