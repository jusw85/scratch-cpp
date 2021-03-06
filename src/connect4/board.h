/*
 * board.h
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#ifndef SCRATCH_BOARD_H
#define SCRATCH_BOARD_H

#include "constants.h"
#include "helpers.h"

enum class Chip {
    X, O
};

enum class CellState {
    X, O, EMPTY
};

class Board {
public:
    Board();

    bool has_empty_cell() const;

    bool has_won(Chip c) const;

    CellState get_cell(int y, int x) const;

    CellState get_cell(const Point &pos) const;

    bool play_chip(int x, Chip c);

    bool remove_chip(int x);

    bool clear_cell(int y, int x);

    bool clear_cell(const Point &pos);

private:
    CellState grid[GRID_HEIGHT][GRID_WIDTH];
};

inline Chip other_chip(Chip chip) {
    return chip == Chip::X ? Chip::O : Chip::X;
}

#endif
