#include <SDL2/SDL.h>
#include "stars.h"
#include "utils.h"

SDL_Rect stars[MAX_STARS];

int init_stars(void)
{
  for(int i = 0; i < MAX_STARS; ++i){
    stars[i].x = randFromRange(0, 840);
    stars[i].y = randFromRange(0, 640);
    stars[i].w = STAR_WIDTH;
    stars[i].h = STAR_HEIGHT;
  }

  return 1; 
}

void update_stars(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for(int i = 0; i < MAX_STARS; ++i){
    stars[i].y += 1;

    if(stars[i].y >= 640){
      stars[i].y = 0;
    }

    SDL_RenderFillRect(renderer, &stars[i]);
  }
}

