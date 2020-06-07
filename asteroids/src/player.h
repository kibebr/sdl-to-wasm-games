#ifndef PLAYER
#define PLAYER


#define BULLET_WIDTH 2
#define BULLET_HEIGHT 2
#define BULLET_SPEED 3

#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 5

#define PLAYER_MAX_VEL 2
#define PLAYER_MAX_BACKWARDS_VEL -1

#define PLAYER_TURNING_SPEED 3

enum DIRECTION
{
  LEFT=0, 
  RIGHT=1, 
  UP=2, 
  DOWN=3
};



int init_player(void);
void render_player(SDL_Renderer* renderer);
void update_player(void);
void player_shoot(void);
void move_player(int dir);
void free_player(void);

#endif