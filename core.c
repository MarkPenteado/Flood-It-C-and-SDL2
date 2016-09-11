#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

// global variables
SDL_Rect r_vermelho, r_verde, r_azul, r_amarelo, r_rosa, r_preto, message_rect;
SDL_Rect matrix_rect[15][15];
TTF_Font* sans;
SDL_Color color = {255, 255, 255};
SDL_Surface* surface; 
SDL_Texture* message;
char text[32];
int matrix_number[15][15], totalMoviments, maxMoviments, xMouse, yMouse;
int matrix_control[15][15];
bool running;

core* createCore(window** window, renderer** renderer) {
	core *newCore = (core*)malloc(sizeof(core));
	if(newCore == NULL) {
		printf("newCore could not be created!\n");
		return NULL;
	}
	newCore->window = *window;
	newCore->renderer = *renderer;
	return newCore;
}

void start_matrix() {
	int i, j, tmp_x = 200, tmp_y = 90;
	
	srand(time(NULL));

	for(i = 0; i < 15; i++) {
		for(j = 0; j < 15; j++) {
			matrix_number[i][j] = rand() % 6 + 0;
			matrix_control[i][j] = 0;
		}
	}

	for(i = 0; i < 15; i++) {
		for(j = 0; j < 15; j++) {
			matrix_rect[i][j].x = tmp_x;
			matrix_rect[i][j].y = tmp_y;
			matrix_rect[i][j].w = 25;
			matrix_rect[i][j].h = 25;
			tmp_x += 25;
		}
		tmp_x = 200;
		tmp_y += 25;
	}
}

// set the settings befor starting the game
void start(core** core) {
	r_vermelho.x = 160;
	r_vermelho.y = 25;
	r_vermelho.w = 80;
	r_vermelho.h = 50;

	r_verde.x = r_vermelho.x + 85;
	r_verde.y = r_vermelho.y;
	r_verde.w = 80;
	r_verde.h = 50;

	r_azul.x = r_verde.x + 85;
	r_azul.y = r_vermelho.y;
	r_azul.w = 80;
	r_azul.h = 50;		

	r_amarelo.x = r_azul.x + 85;
	r_amarelo.y = r_vermelho.y;
	r_amarelo.w = 80;
	r_amarelo.h = 50;

	r_rosa.x = r_amarelo.x + 85;
	r_rosa.y = r_vermelho.y;
	r_rosa.w = 80;
	r_rosa.h = 50;

	r_preto.x = r_rosa.x + 85;
	r_preto.y = r_vermelho.y;
	r_preto.w = 80;
	r_preto.h = 50;

	// display maxMoviments - totalMoviments
	totalMoviments = 0;
	maxMoviments = 30;

	// start text
	sprintf(text, "Restam %d movimentos", maxMoviments-totalMoviments);
	sans = TTF_OpenFont("./OpenSans-Regular.ttf", 16);
	surface = TTF_RenderText_Solid(sans, text, color);
	message = SDL_CreateTextureFromSurface((*core)->renderer->sdl_renderer, surface);
	message_rect.x = 460 - surface->w;  //controls the rect's x coordinate 
	message_rect.y = 560; // controls the rect's y coordinte
	message_rect.w = surface->w; // controls the width of the rect
	message_rect.h = surface->h; // controls the height of the rect

	// start matrix
	start_matrix();

	// mouse coord
	xMouse = 0;
	yMouse = 0;

	running = true;

	matrix_control[0][0] = 1;
}

void drawRect(core** core, SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    setRenderDrawColor(&((*core)->renderer), r, g, b, a); // set rect color
    SDL_RenderFillRect((*core)->renderer->sdl_renderer, &rect);  // render rect
}

void flood(int i, int j, int color) {
	if((i > -1 && i < 15) && (j > -1 && j < 15)) {
	    if (matrix_control[i][j] == 0 && matrix_number[i][j] == color) {
	    	matrix_control[i][j] = 1;
	        flood(i + 1, j, color);
	        flood(i - 1, j, color);
	        flood(i, j + 1, color);
	        flood(i, j - 1, color);
	    }
	}
}
 
void solveGameMyHeuristic(int color) {
	int i, j;
	for(i = 0;i < 15; i++) {
		for(j = 0; j < 14; j++) {
			if(matrix_control[i][j] == 1 && matrix_number[i][j + 1] == color) {
				flood(i, j + 1, color);
			}
		}
	}
	for(i = 0; i < 14; i++) {
		for(j = 0; j < 15; j++) {
			if(matrix_control[i][j] == 1 && matrix_number[i + 1][j] == color) {
				flood(i + 1, j, color);
			}
		}
	}
	for(i = 1; i < 15; i++) {
		for(j = 0; j < 15; j++) {
			if(matrix_control[i][j] == 1 && matrix_number[i - 1][j] == color) {
				flood(i - 1, j, color);
			}
		}
	}
	for(i = 0; i < 15; i++) {
		for(j = 1; j < 15; j++) {
			if(matrix_control[i][j] == 1 && matrix_number[i][j - 1] == color) {
				flood(i, j - 1, color);
			}
		}
	}
	for(i = 0; i < 15; i++) {
		for(j = 0; j < 15; j++) {
			if(matrix_control[i][j] == 1) {
				matrix_number[i][j] = color;
			}
		}
	}
}

void mouseClick(int x, int y) {
	if((xMouse > r_vermelho.x) && (xMouse < r_vermelho.x + r_vermelho.w) 
		&& (yMouse > r_vermelho.y) && (yMouse < r_vermelho.y + r_vermelho.h)) {
		printf("Vermelho\n");
		solveGameMyHeuristic(0);
	}

	if((xMouse > r_verde.x) && (xMouse < r_verde.x + r_verde.w) 
		&& (yMouse > r_verde.y) && (yMouse < r_verde.y + r_verde.h)) {
		printf("Verde\n");
		solveGameMyHeuristic(1);
	}	

	if((xMouse > r_azul.x) && (xMouse < r_azul.x + r_azul.w) 
		&& (yMouse > r_azul.y) && (yMouse < r_azul.y + r_azul.h)) {
		printf("Azul\n");
		solveGameMyHeuristic(2);
	}

	if((xMouse > r_amarelo.x) && (xMouse < r_amarelo.x + r_amarelo.w) 
		&& (yMouse > r_amarelo.y) && (yMouse < r_amarelo.y + r_amarelo.h)) {
		printf("Amarelo\n");
		solveGameMyHeuristic(3);
	}

	if((xMouse > r_rosa.x) && (xMouse < r_rosa.x + r_rosa.w) 
		&& (yMouse > r_rosa.y) && (yMouse < r_rosa.y + r_rosa.h)) {
		printf("Rosa\n");
		solveGameMyHeuristic(4);
	}

	if((xMouse > r_preto.x) && (xMouse < r_preto.x + r_preto.w) 
		&& (yMouse > r_preto.y) && (yMouse < r_preto.y + r_preto.h)) {
		printf("Preto\n");
		solveGameMyHeuristic(5);
	}	
}

void updateText(core** core, char *str) {
	surface = TTF_RenderText_Solid(sans, str, color);
	message = SDL_CreateTextureFromSurface((*core)->renderer->sdl_renderer, surface);
	SDL_RenderCopy((*core)->renderer->sdl_renderer, message, NULL, &message_rect);
	SDL_DestroyTexture(message);
    SDL_FreeSurface(surface);	
}

// main game logic
void update(core** core) {
	int win;
	while(running) {
		win = 1;
		SDL_Event e;
        if (SDL_PollEvent(&e)) {
        	 // close game on X button
            if (e.type == SDL_QUIT) {
                running = false;
            }
            // get mouse position
            if(e.type == SDL_MOUSEMOTION) {
            	xMouse = e.motion.x;
            	yMouse = e.motion.y;
            }
            // get mouse click
            if (e.type == SDL_MOUSEBUTTONDOWN) {
            	if (e.button.button == SDL_BUTTON_LEFT) {
            		printf("botao esquerdo do mouse pressionado\n");
            		mouseClick(xMouse, yMouse);
            		totalMoviments++;
            	}
            }
            // get keyboar input
            if(e.type == SDL_KEYDOWN) {
            	if(e.key.keysym.sym == SDLK_r) {
            		printf("tecla R pressionada, numero de jogadas: 30\n");
            		totalMoviments = 0;
            	}
            }
        }
        setRenderDrawColor(&((*core)->renderer), 100, 100, 100, 255); // set background color
		renderClear(&((*core)->renderer)); // clear screen

		// draw principal rects
		drawRect(core, r_vermelho, 255, 0, 0, 255);
		drawRect(core, r_verde, 0, 255, 0, 255);
		drawRect(core, r_azul, 0, 0, 255, 255);
		drawRect(core, r_amarelo, 255, 255, 0, 255);
		drawRect(core, r_rosa, 255, 0, 255, 255);
		drawRect(core, r_preto, 0, 0, 0, 255);

		// draw matrix_rect
		int i, j;
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
				if(matrix_number[i][j] == 0) drawRect(core, matrix_rect[i][j], 255, 0, 0, 255);
				if(matrix_number[i][j] == 1) drawRect(core, matrix_rect[i][j], 0, 255, 0, 255);
				if(matrix_number[i][j] == 2) drawRect(core, matrix_rect[i][j], 0, 0, 255, 255);
				if(matrix_number[i][j] == 3) drawRect(core, matrix_rect[i][j], 255, 255, 0, 255);
				if(matrix_number[i][j] == 4) drawRect(core, matrix_rect[i][j], 255, 0, 255, 255);
				if(matrix_number[i][j] == 5) drawRect(core, matrix_rect[i][j], 0, 0, 0, 255);
			}
		}

		// display text		
		sprintf(text, "Restam %d movimentos", maxMoviments-totalMoviments);
		updateText(core, text);

    	renderPresent(&((*core)->renderer)); // update screen

		// lose game
		if(maxMoviments-totalMoviments < 1) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
				"Fim!",
                "Voce ultrapassou a quantidade maxima de jogadas!\n                  Voce perdeu!", 
                NULL);
			exit(0);
		}

		// win game
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
				if(matrix_control[i][j] != 1) {
					win = 0;
				}
			}
		}
		if(win) {
			char buffer[32];
			sprintf(buffer, "Voce venceu com %d jogadas!", maxMoviments-totalMoviments);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"Fim!",
	            buffer, NULL);
			exit(0);
		}
    }
}

void destroyCore(core** core) {
	if(*core != NULL) {
		free(*core);
		*core = NULL;
	}
}