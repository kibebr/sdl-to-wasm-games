#include <SDL2/SDL.h>
#include <math.h>
#include "player.h"
#include "globals.h"
#include "utils.h"

struct Triangle{
  double x1, y1;
  double x2, y2;
  double x3, y3;
};

struct BulletNode{
  SDL_Rect rect;
  float _x, _y;
  double deg;
  struct BulletNode *next;
  struct BulletNode *previous;
};
struct BulletNode *bullet_head;

struct Player{
  int width, height;
  double x, y;
  double velocity;
  float deg;
  struct Triangle triangle;
};

struct Player player;

int init_player(void)
{
  player.width = PLAYER_WIDTH;
  player.height = PLAYER_HEIGHT;
  player.x = SCREEN_WIDTH / 2;
  player.y = SCREEN_HEIGHT / 2;

  bullet_head = NULL;

  return 0;
}

void render_bullets(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 124, 252, 0, SDL_ALPHA_OPAQUE);

  for(struct BulletNode *ptr = bullet_head; ptr != NULL; ptr = (*ptr).next){
    (*ptr)._x += sin(deg2rad((*ptr).deg)) * 2;
    (*ptr)._y -= cos(deg2rad((*ptr).deg)) * 2;
    (*ptr).rect.x = (int)(*ptr)._x;
    (*ptr).rect.y = (int)(*ptr)._y;

    SDL_RenderFillRect(renderer, &(*ptr).rect);
  }
}

void render_player(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 124, 252, 0, SDL_ALPHA_OPAQUE);

  SDL_RenderDrawLine(renderer, player.triangle.x1, 
                               player.triangle.y1, 
                               player.triangle.x2, 
                               player.triangle.y2);

  SDL_RenderDrawLine(renderer, player.triangle.x2, 
                               player.triangle.y2, 
                               player.triangle.x3, 
                               player.triangle.y3);

  SDL_RenderDrawLine(renderer, player.triangle.x3, 
                               player.triangle.y3, 
                               player.triangle.x1, 
                               player.triangle.y1);

  render_bullets(renderer);
}


void update_triangle(void)
{
  player.triangle.x1 = player.x + 
                       ((player.x - player.width) - player.x) * 
                       cos(deg2rad(player.deg)) - 
                       ((player.y + player.height + player.width) - player.y) * 
                       sin(deg2rad(player.deg));

  player.triangle.y1 = player.y + 
                       ((player.x - player.width) - player.x) * 
                       sin(deg2rad(player.deg)) + 
                       ((player.y + player.height + player.width) - player.y) * 
                       cos(deg2rad(player.deg));

  player.triangle.x2 = player.x + 
                       (player.x - player.x) * 
                       cos(deg2rad(player.deg)) - 
                       ((player.y - player.height) - player.y) * 
                       sin(deg2rad(player.deg));

  player.triangle.y2 = player.y + 
                       (player.x - player.x) * 
                       sin(deg2rad(player.deg)) + 
                       ((player.y - player.height) - player.y) * 
                       cos(deg2rad(player.deg));

  player.triangle.x3 = player.x + 
                       ((player.x + player.width) - player.x) * 
                       cos(deg2rad(player.deg)) - 
                       ((player.y + (player.height * 2 + 5)) - player.y) * 
                       sin(deg2rad(player.deg));

  player.triangle.y3 = player.y + 
                       ((player.x + player.width) - player.x) * 
                       sin(deg2rad(player.deg)) + 
                       ((player.y + (player.height * 2 + 5)) - player.y) * 
                       cos(deg2rad(player.deg));
}

void player_shoot(void)
{
  struct BulletNode *new_bullet = malloc(sizeof(struct BulletNode));
  if(new_bullet == NULL){
    exit(1);
  }

  (*new_bullet)._x = player.x - 2;
  (*new_bullet)._y = player.y;
  (*new_bullet).rect.x = (int)(*new_bullet)._x;
  (*new_bullet).rect.y = (int)(*new_bullet)._y;
  (*new_bullet).deg = player.deg;
  (*new_bullet).rect.w = BULLET_WIDTH;
  (*new_bullet).rect.h = BULLET_HEIGHT;
  (*new_bullet).next = NULL;

  if(bullet_head == NULL){
    bullet_head = new_bullet;
  }
  else{
    struct BulletNode *ptr = bullet_head;
    while((*ptr).next != NULL){
      ptr = (*ptr).next;
    }
    (*ptr).next = new_bullet;
  }
}

void update_player(void)
{
  update_triangle();

  player.x += sin(deg2rad(player.deg)) * player.velocity;
  player.y -= cos(deg2rad(player.deg)) * player.velocity;

  if(player.deg == 360 || player.deg == -360){
    player.deg = 0;
  }
}

void move_player(int dir)
{
  switch(dir){
    case UP:
      if(player.velocity <= PLAYER_MAX_VEL){
        player.velocity += 0.05;
      }
      break;
    case DOWN:
      if(player.velocity >= PLAYER_MAX_BACKWARDS_VEL){
        player.velocity -= 0.05;
      }
      break;
    case LEFT:
      player.deg-=3;
      break;
    case RIGHT:
      player.deg+=3;
      break;
  }
}

void free_player(void)
{
  struct BulletNode *ptr = bullet_head;
  struct BulletNode *tmp = NULL;

  while(ptr != NULL){
    tmp = ptr;
    ptr = (*ptr).next;
    free(tmp);
  }
}