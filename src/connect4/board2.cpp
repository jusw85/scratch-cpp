/*
 * board.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include <cstdint>
#include "board2.h"

CellState chip_to_cellstate(Chip c) {
    return c == Chip::X ? CellState::X : CellState::O;
}

// https://blog.gamesolver.org/solving-connect-four/06-bitboard/
Board::Board() {
    for (int col = 0; col < GRID_WIDTH; ++col) {
        bottom_mask[col] = UINT64_C(1) << col * (GRID_HEIGHT + 1);
        top_mask[col] = bottom_mask[col] << (GRID_HEIGHT - 1);
        top_masks |= top_mask[col];
    }
}

bool Board::has_empty_cell() const {
    return (all_pos & top_masks) != top_masks;
}

// https://towardsdatascience.com/creating-the-perfect-connect-four-ai-bot-c165115557b0
bool Board::has_won(Chip c) const {
    uint64_t pos = c == Chip::X ? x_pos : o_pos;

    // - horizontal
    uint64_t m = pos & (pos >> (GRID_HEIGHT + 1));
    if (m & (m >> (2 * (GRID_HEIGHT + 1)))) return true;

    // \ diagonal 1
    m = pos & (pos >> GRID_HEIGHT);
    if (m & (m >> (2 * GRID_HEIGHT))) return true;

    // / diagonal 2
    m = pos & (pos >> (GRID_HEIGHT + 2));
    if (m & (m >> (2 * (GRID_HEIGHT + 2)))) return true;

    // | vertical
    m = pos & (pos >> 1);
    if (m & (m >> 2)) return true;

    return false;
}

CellState Board::get_cell(int y, int x) const {
    uint64_t p = (UINT64_C(1) << x * (GRID_HEIGHT + 1)) << y;
    if (x_pos & p) {
        return CellState::X;
    } else if (o_pos & p) {
        return CellState::O;
    } else {
        return CellState::EMPTY;
    }
}

CellState Board::get_cell(const Point &pos) const {
    return get_cell(pos.y, pos.x);
}

bool Board::play_chip(int x, Chip c) {
    if (all_pos & top_mask[x]) return false;
    all_pos |= all_pos + bottom_mask[x];
    if (c == Chip::X) {
        x_pos = all_pos ^ o_pos;
    } else {
        o_pos = all_pos ^ x_pos;
    }
    return true;
}

bool Board::remove_chip(int x) {
    if (!(all_pos & bottom_mask[x])) return false;
    int y = 1;
    for (; all_pos & (bottom_mask[x] << y); y++);
    y--;
    all_pos -= (bottom_mask[x] << y);
    x_pos &= all_pos;
    o_pos &= all_pos;
    return true;
}

uint64_t Board::get_key() const {
    return x_pos + all_pos;
}