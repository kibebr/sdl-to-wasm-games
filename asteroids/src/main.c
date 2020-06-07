#include <SDL2/SDL.h>
#include <stdio.h>
#include "main.h"
#include "stars.h"
#include "player.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;
const Uint8 *keystate;

void quit_game();
void handle_events();

int init_SDL(void)
{
  window = NULL;
  renderer = NULL;

  if(SDL_Init(SDL_INIT_VIDEO) > 0)
    return NO_SDL;

  window = SDL_CreateWindow("ASTEROIDS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(!window)
    return NO_WINDOW;

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );


  keystate = SDL_GetKeyboardState(NULL);

  return 0;
}

int init_game(void)
{
  init_stars();
  init_player();
  return 0;
}

void main_loop(void)
{ 
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  update_stars(renderer);
  render_player(renderer);
  update_player();

  SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
  init_SDL();
  init_game();

  while(1){
    handle_events();
    main_loop();
    SDL_Delay(16);
  }
}


void handle_events()
{
  while(SDL_PollEvent(&e) != 0){
    if(e.type == SDL_QUIT){
      quit_game();
    }
  }

  if(keystate[SDL_SCANCODE_UP]){
    move_player(UP);
  }

  if(keystate[SDL_SCANCODE_DOWN]){
    move_player(DOWN);
  }

  if(keystate[SDL_SCANCODE_LEFT]){
    move_player(LEFT);
  }

  if(keystate[SDL_SCANCODE_RIGHT]){
    move_player(RIGHT);
  }

  if(keystate[SDL_SCANCODE_SPACE]){
    player_shoot();
  }
}

void quit_game(void)
{
  SDL_DestroyWindow(window);
  window = NULL;

  SDL_DestroyRenderer(renderer);
  renderer = NULL;


  free_player();
  SDL_Quit();
}