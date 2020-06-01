/*
 * ai.h
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#ifndef SCRATCH_AI_H_
#define SCRATCH_AI_H_

#include "board2.h"
#include "transtable.h"

class Solver {
public:
    Solver();

    bool find_best_move(Board &b, Chip player, int &move);

private:
    TranspositionTable table;

    int column_order[GRID_WIDTH] = {};

    int negamaxab(Board &b, Chip current_player, int depth, int &move, bool first_move, int alpha, int beta);
};

#endif
