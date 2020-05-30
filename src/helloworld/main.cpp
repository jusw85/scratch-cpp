/*
 * main.cpp
 *
 *  Created on: 09/09/2010
 *      Author: WCHOONTE
 */

#include "SDL.h"

using namespace std;

int main(int argc, char *args[]) {
    SDL_Surface *hello = NULL;
    SDL_Surface *screen = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    hello = SDL_LoadBMP("../data/hello.bmp");
    SDL_BlitSurface(hello, NULL, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(2000);
    SDL_FreeSurface(hello);
    SDL_Quit();
    return 0;
}
