#include "board.h"

CellState chip_to_cellstate(Chip c) {
    return c == Chip::X ? CellState::X : CellState::O;
}

Board::Board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = CellState::EMPTY;
        }
    }
}

bool Board::has_empty_cell() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == CellState::EMPTY)
                return true;
        }
    }
    return false;
}

bool Board::has_won(Chip c) const {
    CellState cs = chip_to_cellstate(c);
    if ((grid[0][0] == cs && grid[0][1] == cs && grid[0][2] == cs) ||
        (grid[1][0] == cs && grid[1][1] == cs && grid[1][2] == cs) ||
        (grid[2][0] == cs && grid[2][1] == cs && grid[2][2] == cs) ||
        (grid[0][0] == cs && grid[1][0] == cs && grid[2][0] == cs) ||
        (grid[0][1] == cs && grid[1][1] == cs && grid[2][1] == cs) ||
        (grid[0][2] == cs && grid[1][2] == cs && grid[2][2] == cs) ||
        (grid[0][0] == cs && grid[1][1] == cs && grid[2][2] == cs) ||
        (grid[0][2] == cs && grid[1][1] == cs && grid[2][0] == cs)) {
        return true;
    }
    return false;
}

bool Board::play_chip(int y, int x, Chip c) {
    if (grid[y][x] == CellState::EMPTY) {
        grid[y][x] = chip_to_cellstate(c);
        return true;
    }
    return false;
}

bool Board::play_chip(const Point &pos, Chip c) {
    return play_chip(pos.y, pos.x, c);
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

CellState Board::get_cell(int y, int x) const {
    return grid[y][x];
}

CellState Board::get_cell(const Point &pos) const {
    return grid[pos.y][pos.x];
}
