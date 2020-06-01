/*
 * ai.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include "ai.h"
#include "constants.h"

// numBytes = (64MB * 1024 * 1024)
// numBits = numBytes * 8
// size = numBits / (64bits per element) = 8388608
// 8388593 prime
// https://stackoverflow.com/questions/1145217/why-should-hash-functions-use-a-prime-number-modulus
// https://cs.stackexchange.com/questions/11029/why-is-it-best-to-use-a-prime-number-as-a-mod-in-a-hashing-function
//Solver::Solver() : table(8388593) {
Solver::Solver() : table(997) {
    
//    https://blog.gamesolver.org/solving-connect-four/05-move-exploration-order/
//               i = 0 1 2 3 4 5 6
//    column_order = 3 2 4 1 5 0 6
//    GRID_WIDTH / 2 = 3
//    (-2 * (i % 2))     = 0, -2, 0, -2, 0, -2, 0
//    (-2 * (i % 2) + 1) = 1, -1, 1, -1, 1, -1, 1
//    (i + 1) / 2        = 0,  1, 1,  2, 2,  3, 3
    for (int i = 0; i < GRID_WIDTH; i++) {
        column_order[i] = GRID_WIDTH / 2 + (-2 * (i % 2) + 1) * (i + 1) / 2;
//        printf("%d\n", column_order[i]);
    }
    table.reset();
}

int Solver::negamaxab(Board &b, Chip current_player, int depth,
                      int &move, bool first_move, int alpha, int beta) {
    if (b.has_won(current_player)) {
        return 1;
    } else if (b.has_won(other_chip(current_player))) {
        return -1;
    } else if (depth <= 0 || !b.has_empty_cell()) {
        return 0;
    }

    int maxvalue = -2;
    int best_move;
    uint8_t val;
//    if (table.get(b.get_key(), val)) {
//        return val;
//    }
    for (int x = 0; x < GRID_WIDTH; x++) {
        int col = column_order[x];
        if (b.play_chip(col, current_player)) {
            int value = -negamaxab(b, other_chip(current_player), depth - 1,
                                   move, false, -beta, -alpha);
            b.remove_chip(col);

            if (value > maxvalue) {
                maxvalue = value;
                best_move = col;
            }
            if (value > alpha) {
                alpha = value;
            }
            if (alpha >= beta) {
                break;
            }
        }
    }
    if (first_move) {
        move = best_move;
    }
//    table.put(b.get_key(), maxvalue);
    return maxvalue;
}

bool Solver::find_best_move(Board &b, Chip player, int &move) {
    if (b.has_won(player) ||
        b.has_won(other_chip(player)) ||
        !b.has_empty_cell()) {
        return false;
    }
    negamaxab(b, player, 50, move, true, -2, 2);
    return true;
}
