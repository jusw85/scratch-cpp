/*
 * ai.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include "ai.h"

#include <cstddef>

int Minimax(BoardState *board, const int depth, const int alpha,
    const int beta, int *move[]) {

  /*
   if (b.has_won(b.turn)) {
   return 1;
   } else if (b.has_won(OtherPlayer(b.turn))) {
   return -1;
   } else if (!b.has_moves()) {
   return 0;
   }
   */

  int *bestmove = new int[2];
  int bestvalue = -2, value;
  int localalpha = alpha;

  for (int y = 0; y < 3; ++y) {
    for (int x = 0; x < 3; ++x) {
      if ((*board).grid()[y][x] == BoardState::E) {
        (*board).MakeMove(x);
        value = -Minimax(board, depth - 1, -beta, -localalpha, NULL);
        (*board).UndoMove(x);

        if (value >= bestvalue) {
          bestvalue = value;
          bestmove[0] = y;
          bestmove[1] = x;
        }

        if (bestvalue >= beta) break;
        if (bestvalue > alpha) localalpha = bestvalue;
      }
    }
  }

  if (move != NULL) *move = bestmove;
  return bestvalue;
}

int *GetMove(BoardState *board) {
  int *move = NULL;
  Minimax(board, 10, -2, 2, &move);
  return move;
}
