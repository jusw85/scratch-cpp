#ifndef SCRATCH_BOARD_H
#define SCRATCH_BOARD_H

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

    bool play_chip(int y, int x, Chip c);

    bool play_chip(const Point &pos, Chip c);

    bool clear_cell(int y, int x);

    bool clear_cell(const Point &pos);

private:

    CellState grid[3][3];
};

#endif
