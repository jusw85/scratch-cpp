/*
 * functions.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include "functions.h"

#include <string>

#include "SDL/SDL_image.h"

#include "constants.h"
#include "globals.h"

SDL_Surface *LoadImage(const std::string filename) {
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load(filename.c_str());

  if (loadedImage != NULL) {
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return optimizedImage;
}

bool Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    return false;
  }

  screen = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kScreenBpp,
      SDL_SWSURFACE);

  if (screen == NULL) {
    return false;
  }

  SDL_WM_SetCaption("Connect 4", NULL);

  return true;
}

bool LoadFiles() {
  sprite_x = LoadImage("../data/c4x.png");
  sprite_o = LoadImage("../data/c4o.png");
  sprite_win = LoadImage("../data/win.png");
  sprite_lose = LoadImage("../data/lose.png");
  sprite_draw = LoadImage("../data/draw.png");

  if (sprite_x == NULL || sprite_o == NULL || sprite_win == NULL || sprite_lose
      == NULL) {
    return false;
  }

  return true;
}

void CleanUp() {
  SDL_FreeSurface(sprite_x);
  SDL_FreeSurface(sprite_o);
  SDL_FreeSurface(sprite_win);
  SDL_FreeSurface(sprite_lose);
  SDL_FreeSurface(sprite_draw);
  SDL_Quit();
}

