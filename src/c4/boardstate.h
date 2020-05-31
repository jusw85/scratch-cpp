/*
 * classes.h
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#ifndef BOARDSTATE_H_
#define BOARDSTATE_H_

#include "constants.h"
#include "functions.h"

class BoardState {
 public:
  enum Chip { X, O, E };

  BoardState();

  bool HasWon() const;
  bool HasMoves() const;
  bool MakeMove(const int column);
  bool UndoMove(const int column);

  const Chip (&grid() const)[kGridHeight][kGridWidth] { return grid_; }
  const Chip lastplayer() const { return lastplayer_; }

 private:
  enum Direction {
        Direction_Begin,
        NW = Direction_Begin,
        N, NE, EE,
        SE, S, SW, W,
        Direction_End
      };

  bool CheckWin(const int row, const int column, const int depth,
          const Direction d) const;
  int GetTopChip(const int column) const;

  Chip grid_[kGridHeight][kGridWidth];
  Chip turn_;
  Chip lastplayer_;
  int lastmove_;
  DISALLOW_COPY_AND_ASSIGN(BoardState);
};

inline BoardState::Chip OtherPlayer(BoardState::Chip p) {
  return (p == BoardState::X ? BoardState::O : BoardState::X);
}

#endif /* BOARDSTATE_H_ */
