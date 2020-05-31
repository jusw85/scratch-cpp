/*
 * boardstate.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include "boardstate.h"

#include "assert.h"

#include <cstddef>

BoardState::BoardState() {
  for (int y = 0; y < kGridHeight; y++) {
    for (int x = 0; x < kGridWidth; x++) {
      grid_[y][x] = E;
    }
  }
  turn_ = X;
  lastmove_ = -1;
  lastplayer_ = E;
}

bool BoardState::HasWon() const {
  int column = lastmove_;
  int row = GetTopChip(column);
  if ( row < 0 || column < 0) return false;
  assert(grid_[row][column] == lastplayer_);

  for (int i = Direction_Begin; i != Direction_End; ++i) {
    if (CheckWin(row, column, 3, static_cast<Direction> (i))) {
      return true;
    }
  }
  return false;
}

bool BoardState::HasMoves() const {
  for (int y = 0; y < kGridHeight; y++) {
    for (int x = 0; x < kGridWidth; x++) {
      if (grid_[y][x] == E) return true;
    }
  }
  return false;
}

bool BoardState::MakeMove(const int column) {
  for (int y = kGridHeight - 1; y >= 0; y--) {
    if (grid_[y][column] == E) {
      lastmove_ = column;
      lastplayer_ = turn_;
      grid_[y][column] = turn_;
      turn_ = OtherPlayer(turn_);
      return true;
    }
  }
  return false;

}

bool BoardState::UndoMove(const int column) {
  int row = GetTopChip(column);
  if (row == -1 || grid_[row][column] != OtherPlayer(turn_)) {
    return false;
  } else {
    lastmove_ = -1;
    lastplayer_ = E;
    grid_[row][column] = E;
    turn_ = OtherPlayer(turn_);
    return true;
  }
}

int BoardState::GetTopChip(const int column) const {
  for (int y = 0; y < kGridHeight; ++y) {
    if (grid_[y][column] != E) {
      return y;
    }
  }
  return -1;
}

bool BoardState::CheckWin(const int in_row, const int in_column,
    const int depth, const Direction d) const {
  if (depth == 0) return true;
  int row = in_row, column = in_column;
  switch (d) {
  case N:
    --row; break;
  case NE:
    --row; ++column; break;
  case EE:
    ++column; break;
  case SE:
    ++row; ++column; break;
  case S:
    ++row; break;
  case SW:
    ++row; --column; break;
  case W:
    --column; break;
  case NW:
    --row; --column; break;
  default:
    assert(false); break;
  }
  if (row < 0 || column < 0 || row >= kGridWidth || column >= kGridHeight)
    return false;
  if (grid_[row][column] != lastplayer_)
    return false;
  return CheckWin(row, column, depth - 1, d);
}
