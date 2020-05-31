/*
 * main.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include "SDL/SDL.h"

#include "ai.h"
#include "boardstate.h"
#include "constants.h"
#include "functions.h"
#include "globals.h"

/* main */
int main(int argc, char* args[]) {
  if (!Init()) return 1;
  if (!LoadFiles()) return 1;

  SDL_Event event;
  BoardState board;
  int col = 0;
  bool quit = false;

  while (!quit) {
    // events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          col--;
          break;
        case SDLK_RIGHT:
          col++;
          break;
        case SDLK_RETURN:
          board.MakeMove(col);
          break;
        case SDLK_ESCAPE:
          quit = true;
          break;
        default:
          break;
        }
      } else if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

    // logic
    if (col < 0) col = 0;
    if (col > kGridWidth - 1) col = kGridWidth - 1;

    /*
     if (board.turn == O) {
     int *move = getMove(&board);
     if (move != NULL) {
     board.make_move(move[0]);
     delete[] (move);
     }
     }
     */

    // draw
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format,
        kGridColour[0], kGridColour[1], kGridColour[2]));

    SDL_Rect hilite;
    hilite.w = kBoxWidth;
    hilite.h = kBoxHeight * kGridHeight;
    hilite.x = col * kBoxWidth;
    hilite.y = 0;
    SDL_FillRect(screen, &hilite, SDL_MapRGB(screen->format,
        kGridHiliteColour[0], kGridHiliteColour[1], kGridHiliteColour[2]));

    SDL_Rect box;
    box.w = kBoxWidth;
    box.h = kBoxHeight;
    for (int y = 0; y < kGridHeight; y++) {
      for (int x = 0; x < kGridWidth; x++) {
        if (board.grid()[y][x] == BoardState::X) {
          box.x = x * kBoxWidth;
          box.y = y * kBoxHeight;
          SDL_BlitSurface(sprite_x, NULL, screen, &box);
        }
        if (board.grid()[y][x] == BoardState::O) {
          box.x = x * kBoxWidth;
          box.y = y * kBoxHeight;
          SDL_BlitSurface(sprite_o, NULL, screen, &box);
        }
      }
    }

    if (board.HasWon()) {
      if (board.lastplayer() == BoardState::X) {
        SDL_BlitSurface(sprite_win, NULL, screen, NULL);
      } else if (board.lastplayer() == BoardState::O) {
        SDL_BlitSurface(sprite_lose, NULL, screen, NULL);
      }
    } else if (!board.HasMoves()) {
      SDL_BlitSurface(sprite_draw, NULL, screen, NULL);
    }

    if (SDL_Flip(screen)) return 1;
  } // end main loop

  CleanUp();
  return 0;
}
