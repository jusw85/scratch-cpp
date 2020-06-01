/*
 * main.cpp
 *
 *  Created on: Sep 6, 2010
 *      Author: wongct
 *
 */

#include <SDL.h>
#include "constants.h"
#include "helpers.h"
#include "app.h"
#include "board.h"
#include "ai.h"

/* main */
int main(int argc, char *args[]) {
    if (!init()) {
        return 1;
    }
    if (!load_assets()) {
        return 1;
    }

    Board board;
    Point cursor;
    cursor.x = 1;
    cursor.y = 1;
    Chip current_player = Chip::X;

    bool quit = false;
    bool game_over = false;
    while (!quit) {
        // events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        cursor.y--;
                        cursor.y = clamp(cursor.y, 0, 2);
                        break;
                    case SDLK_DOWN:
                        cursor.y++;
                        cursor.y = clamp(cursor.y, 0, 2);
                        break;
                    case SDLK_LEFT:
                        cursor.x--;
                        cursor.x = clamp(cursor.x, 0, 2);
                        break;
                    case SDLK_RIGHT:
                        cursor.x++;
                        cursor.x = clamp(cursor.x, 0, 2);
                        break;
                    case SDLK_RETURN:
                        if (!game_over && board.play_chip(cursor, Chip::X)) {
                            current_player = Chip::O;
                        }
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // ai
        if (!game_over && current_player == Chip::O) {
            Point move;
            if (find_best_move(board, Chip::O, move)) {
                if (board.play_chip(move, Chip::O)) {
                    current_player = Chip::X;
                }
            }
        }

        if (board.has_won(Chip::X) || board.has_won(Chip::O)) {
            game_over = true;
        }

        // draw
        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format,
                                                            GRID_COLOUR[0],
                                                            GRID_COLOUR[1],
                                                            GRID_COLOUR[2]));

        SDL_Rect cellRect;
        cellRect.w = CELL_WIDTH;
        cellRect.h = CELL_HEIGHT;
        cellRect.x = cursor.x * CELL_WIDTH;
        cellRect.y = cursor.y * CELL_HEIGHT;

        SDL_FillRect(screen, &cellRect, SDL_MapRGB(screen->format,
                                                   GRID_HILITE_COLOUR[0],
                                                   GRID_HILITE_COLOUR[1],
                                                   GRID_HILITE_COLOUR[2]));

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                CellState cellState = board.get_cell(y, x);
                if (cellState == CellState::X) {
                    cellRect.x = x * CELL_WIDTH;
                    cellRect.y = y * CELL_HEIGHT;
                    SDL_BlitSurface(sprite_x, NULL, screen, &cellRect);
                } else if (cellState == CellState::O) {
                    cellRect.x = x * CELL_WIDTH;
                    cellRect.y = y * CELL_HEIGHT;
                    SDL_BlitSurface(sprite_o, NULL, screen, &cellRect);
                }
            }
        }

        if (board.has_won(Chip::X)) {
            SDL_BlitSurface(sprite_win, NULL, screen, NULL);
        } else if (board.has_won(Chip::O)) {
            SDL_BlitSurface(sprite_lose, NULL, screen, NULL);
        } else if (!board.has_empty_cell()) {
            SDL_BlitSurface(sprite_draw, NULL, screen, NULL);
        }

        if (SDL_Flip(screen)) {
            return 1;
        }

    }

    clean_up();
    return 0;
}
