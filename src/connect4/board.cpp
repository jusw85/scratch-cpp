/*
 * board.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include "board.h"

CellState chip_to_cellstate(Chip c) {
    return c == Chip::X ? CellState::X : CellState::O;
}

Board::Board() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = CellState::EMPTY;
        }
    }
}

bool Board::has_empty_cell() const {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == CellState::EMPTY) {
                return true;
            }
        }
    }
    return false;
}

bool Board::has_won(Chip c) const {
    CellState cs = chip_to_cellstate(c);

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH - 3; x++) {
            if (grid[y][x] == cs) {
                bool won = true;
                for (int i = 1; i < 4; i++) {
                    x++;
                    if (grid[y][x] != cs) {
                        won = false;
                        break;
                    }
                }
                if (won) return true;
            }
        }
    }

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT - 3; y++) {
            if (grid[y][x] == cs) {
                bool won = true;
                for (int i = 1; i < 4; i++) {
                    y++;
                    if (grid[y][x] != cs) {
                        won = false;
                        break;
                    }
                }
                if (won) return true;
            }
        }
    }

    for (int y = 0; y < GRID_HEIGHT - 3; y++) {
        for (int x = 0; x < GRID_WIDTH - 3; x++) {
            if (grid[y][x] == cs) {
                bool won = true;
                for (int i = 1; i < 4; i++) {
                    if (grid[y + i][x + i] != cs) {
                        won = false;
                        break;
                    }
                }
                if (won) return true;
            }
        }
    }
    return false;
}

//bool Board::has_won(Chip c) const {
//    CellState cs = chip_to_cellstate(c);
//
//    for (int y = 0; y < GRID_HEIGHT; y++) {
//        for (int x = 0; x < GRID_WIDTH; x++) {
//            if (grid[y][x] == cs) {
//                bool won = true;
//                for (int i = 1; i < 4; i++) {
//                    if (x + i >= GRID_WIDTH ||
//                        grid[y][x + i] != cs) {
//                        won = false;
//                        break;
//                    }
//                }
//                if (won) return true;
//                won = true;
//                for (int i = 1; i < 4; i++) {
//                    if (y + i >= GRID_HEIGHT ||
//                        grid[y + i][x] != cs) {
//                        won = false;
//                        break;
//                    }
//                }
//                if (won) return true;
//                won = true;
//                for (int i = 1; i < 4; i++) {
//                    if (x + i >= GRID_WIDTH ||
//                        y + i >= GRID_HEIGHT ||
//                        grid[y + i][x + i] != cs) {
//                        won = false;
//                        break;
//                    }
//                }
//                if (won) return true;
//            }
//        }
//    }
//    return false;
//}

CellState Board::get_cell(int y, int x) const {
    return grid[y][x];
}

CellState Board::get_cell(const Point &pos) const {
    return grid[pos.y][pos.x];
}

bool Board::play_chip(int x, Chip c) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        if (grid[y][x] == CellState::EMPTY) {
            grid[y][x] = chip_to_cellstate(c);
            return true;
        }
    }
    return false;
}

bool Board::remove_chip(int x) {
    for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
        if (grid[y][x] != CellState::EMPTY) {
            grid[y][x] = CellState::EMPTY;
            return true;
        }
    }
    return false;
}

bool Board::clear_cell(int y, int x) {
    if (grid[y][x] != CellState::EMPTY) {
        grid[y][x] = CellState::EMPTY;
        return true;
    }
    return false;
}

bool Board::clear_cell(const Point &pos) {
    return clear_cell(pos.y, pos.x);
}
