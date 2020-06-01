#ifndef SCRATCH_APP_H
#define SCRATCH_APP_H

#include <SDL_image.h>

extern SDL_Surface *screen;
extern SDL_Surface *sprite_x;
extern SDL_Surface *sprite_o;
extern SDL_Surface *sprite_win;
extern SDL_Surface *sprite_lose;
extern SDL_Surface *sprite_draw;

bool init();

bool load_assets();

void clean_up();

#endif
