/*
 * board.h
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#ifndef SCRATCH_BOARD2_H
#define SCRATCH_BOARD2_H

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

    uint64_t get_key() const;

private:
    uint64_t x_pos = 0;
    uint64_t o_pos = 0;
    uint64_t all_pos = 0;
    uint64_t top_mask[GRID_WIDTH];
    uint64_t bottom_mask[GRID_WIDTH];
    uint64_t top_masks = 0;
};

inline Chip other_chip(Chip chip) {
    return chip == Chip::X ? Chip::O : Chip::X;
}

#endif
