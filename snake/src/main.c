#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "snake.h"
#include "apple.h"

void handle_events(SDL_Event* e);
void quit(void);

SDL_Window *window;
SDL_Renderer *renderer;

bool running = false;
bool frozen = false;

bool init(void){
	bool success = true;
	window = NULL;
	renderer = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not be initiliazed. SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	window = SDL_CreateWindow("snake game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(!window){
		printf("SDL_Window could not be initialized. SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	
	}

	if(!init_snake()){
		printf("snake could not be initialized.\n");
		success = false;
	}

	generate_new_apple_pos();

	running = true;
	return success;
}

int main(int argc, char* args[])
{
	if(!init())
		return -1;
	else{
		SDL_Event e;

		while(running){
			handle_events(&e);

			if(frozen)
				continue;

			SDL_SetRenderDrawColor(renderer, 255, 255, 224, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);

			update_snake();
			render_apple();

			SDL_RenderPresent(renderer);

			SDL_Delay(50);
		}
	}

	quit_game();
	return 0;
}

void handle_events(SDL_Event *e)
{
	while(SDL_PollEvent(e) != 0){
		if((*e).type == SDL_QUIT){
			running = false;
		}
		else if((*e).type == SDL_KEYDOWN){
			switch((*e).key.keysym.sym){
				case SDLK_RIGHT:
					change_snake_direction(RIGHT);
					break;
				case SDLK_LEFT:
					change_snake_direction(LEFT);
					break;
				case SDLK_UP:
					change_snake_direction(UP);
					break;
				case SDLK_DOWN:
					change_snake_direction(DOWN);
					break;
			}
		}
	}
}

void quit_game(void){
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	free_tails();
	SDL_Quit();
}

void set_freeze(bool b)
{
	frozen = b;
}

SDL_Renderer* getRenderer() { return renderer; }