/*
 * main.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include <SDL.h>
#include "constants.h"
#include "helpers.h"
#include "app.h"
#include "board2.h"
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
    Solver solver;
    int col = 0;
    Chip current_player = Chip::X;

    bool quit = false;
    bool game_over = false;
    while (!quit) {
        // events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        col--;
                        col = clamp(col, 0, GRID_WIDTH - 1);
                        break;
                    case SDLK_RIGHT:
                        col++;
                        col = clamp(col, 0, GRID_WIDTH - 1);
                        break;
                    case SDLK_RETURN:
                        if (!game_over && board.play_chip(col, current_player)) {
                            current_player = other_chip(current_player);
                        }
                        break;
//                    case SDLK_DOWN:
//                        board.remove_chip(col);
//                        break;
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

        // ai
        if (!game_over && current_player == Chip::O) {
            int move;
            if (solver.find_best_move(board, Chip::O, move)) {
                if (board.play_chip(move, Chip::O)) {
                    current_player = other_chip(current_player);
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

        SDL_Rect hilite;
        hilite.w = CELL_WIDTH;
        hilite.h = CELL_HEIGHT * GRID_HEIGHT;
        hilite.x = col * CELL_WIDTH;
        hilite.y = 0;
        SDL_FillRect(screen, &hilite, SDL_MapRGB(screen->format,
                                                 GRID_HILITE_COLOUR[0],
                                                 GRID_HILITE_COLOUR[1],
                                                 GRID_HILITE_COLOUR[2]));


        SDL_Rect cell;
        cell.w = CELL_WIDTH;
        cell.h = CELL_HEIGHT;
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                CellState cellState = board.get_cell(y, x);
                if (cellState == CellState::X) {
                    cell.x = x * CELL_WIDTH;
                    cell.y = (GRID_HEIGHT - 1 - y) * CELL_HEIGHT;
                    SDL_BlitSurface(sprite_x, NULL, screen, &cell);
                }
                if (cellState == CellState::O) {
                    cell.x = x * CELL_WIDTH;
                    cell.y = (GRID_HEIGHT - 1 - y) * CELL_HEIGHT;
                    SDL_BlitSurface(sprite_o, NULL, screen, &cell);
                }
            }
        }

//        printf("%d", board.has_empty_cell());

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
