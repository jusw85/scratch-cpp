/*
 * ai.cpp
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#include <memory>
#include "ai.h"

Chip other_player(Chip player) {
    return player == Chip::X ? Chip::O : Chip::X;
}

int minimax(Board &b, Chip maximising_player, Chip current_player,
            int depth, Point *&move, bool first_move) {
    if (b.has_won(maximising_player)) {
        return 1;
    } else if (b.has_won(other_player(maximising_player))) {
        return -1;
    } else if (depth <= 0 || !b.has_empty_cell()) {
        return 0;
    }

    if (current_player == maximising_player) {
        int maxvalue = -2;
        Point best_move;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (b.get_cell(y, x) == CellState::EMPTY) {
                    b.play_chip(y, x, current_player);
                    int value = minimax(b, maximising_player, other_player(current_player), depth - 1, move, false);
                    b.clear_cell(y, x);

                    if (value >= maxvalue) {
                        maxvalue = value;
                        best_move.y = y;
                        best_move.x = x;
                    }
                }
            }
        }
        if (first_move) {
            move = new Point();
            *move = best_move;
        }
        return maxvalue;
    } else {
        int minvalue = 2;
        Point best_move;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (b.get_cell(y, x) == CellState::EMPTY) {
                    b.play_chip(y, x, current_player);
                    int value = minimax(b, maximising_player, other_player(current_player), depth - 1, move, false);
                    b.clear_cell(y, x);

                    if (value <= minvalue) {
                        minvalue = value;
                        best_move.y = y;
                        best_move.x = x;
                    }
                }
            }
        }
        if (first_move) {
            move = new Point();
            *move = best_move;
        }
        return minvalue;
    }
}

int minimax2(Board &b, Chip maximising_player, Chip current_player,
             int depth, std::unique_ptr<Point> &move, bool first_move) {
    if (b.has_won(maximising_player)) {
        return 1;
    } else if (b.has_won(other_player(maximising_player))) {
        return -1;
    } else if (depth <= 0 || !b.has_empty_cell()) {
        return 0;
    }

    if (current_player == maximising_player) {
        int maxvalue = -2;
        Point best_move;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (b.get_cell(y, x) == CellState::EMPTY) {
                    b.play_chip(y, x, current_player);
                    int value = minimax2(b, maximising_player, other_player(current_player), depth - 1, move, false);
                    b.clear_cell(y, x);

                    if (value >= maxvalue) {
                        maxvalue = value;
                        best_move.y = y;
                        best_move.x = x;
                    }
                }
            }
        }
        if (first_move) {
            move = std::make_unique<Point>();
            *move = best_move;
        }
        return maxvalue;
    } else {
        int minvalue = 2;
        Point best_move;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (b.get_cell(y, x) == CellState::EMPTY) {
                    b.play_chip(y, x, current_player);
                    int value = minimax2(b, maximising_player, other_player(current_player), depth - 1, move, false);
                    b.clear_cell(y, x);

                    if (value <= minvalue) {
                        minvalue = value;
                        best_move.y = y;
                        best_move.x = x;
                    }
                }
            }
        }
        if (first_move) {
            move = std::make_unique<Point>();
            *move = best_move;
        }
        return minvalue;
    }
}

int minimax3(Board &b, Chip maximising_player, Chip current_player,
             int depth, Point &move, bool first_move) {
    if (b.has_won(maximising_player)) {
        return 1;
    } else if (b.has_won(other_player(maximising_player))) {
        return -1;
    } else if (depth <= 0 || !b.has_empty_cell()) {
        return 0;
    }

    if (current_player == maximising_player) {
        int maxvalue = -2;
        Point best_move;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (b.get_cell(y, x) == CellState::EMPTY) {
                    b.play_chip(y, x, current_player);
                    int value = minimax3(b, maximising_player, other_player(current_player), depth - 1, move, false);
                    b.clear_cell(y, x);

                    if (value >= maxvalue) {
                        maxvalue = value;
                        best_move.y = y;
                        best_move.x = x;
                    }
                }
            }
        }
        if (first_move) {
            move = best_move;
        }
        return maxvalue;
    } else {
        int minvalue = 2;
        Point best_move;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (b.get_cell(y, x) == CellState::EMPTY) {
                    b.play_chip(y, x, current_player);
                    int value = minimax3(b, maximising_player, other_player(current_player), depth - 1, move, false);
                    b.clear_cell(y, x);

                    if (value <= minvalue) {
                        minvalue = value;
                        best_move.y = y;
                        best_move.x = x;
                    }
                }
            }
        }
        if (first_move) {
            move = best_move;
        }
        return minvalue;
    }
}

int negamax(Board &b, Chip current_player,
            int depth, Point &move, bool first_move) {
    if (b.has_won(current_player)) {
        return 1;
    } else if (b.has_won(other_player(current_player))) {
        return -1;
    } else if (depth <= 0 || !b.has_empty_cell()) {
        return 0;
    }

    int maxvalue = -2;
    Point best_move;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (b.get_cell(y, x) == CellState::EMPTY) {
                b.play_chip(y, x, current_player);
                int value = -negamax(b, other_player(current_player), depth - 1, move, false);
                b.clear_cell(y, x);

                if (value >= maxvalue) {
                    maxvalue = value;
                    best_move.y = y;
                    best_move.x = x;
                }
            }
        }
    }
    if (first_move) {
        move = best_move;
    }
    return maxvalue;
}

int negamaxab(Board &b, Chip current_player, int depth,
              Point &move, bool first_move, int alpha, int beta) {
    if (b.has_won(current_player)) {
        return 1;
    } else if (b.has_won(other_player(current_player))) {
        return -1;
    } else if (depth <= 0 || !b.has_empty_cell()) {
        return 0;
    }

    int maxvalue = -2;
    Point best_move;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (b.get_cell(y, x) == CellState::EMPTY) {
                b.play_chip(y, x, current_player);
                int value = -negamaxab(b, other_player(current_player), depth - 1,
                                       move, false, -beta, -alpha);
                b.clear_cell(y, x);

                if (value > maxvalue) {
                    maxvalue = value;
                    best_move.y = y;
                    best_move.x = x;
                }
                if (value > alpha) {
                    alpha = value;
                }
                if (alpha >= beta) {
                    break;
                }
            }
        }
    }
    if (first_move) {
        move = best_move;
    }
    return maxvalue;
}

// alpha = best(highest) value maximising player has seen so far, initial = -infinity
// beta = best(lowest) value minimising player has seen so far, initial = infinity
int minimaxab(Board &b, Chip maximising_player, Chip current_player,
              int depth, Point &move, bool first_move, int alpha, int beta) {
    if (b.has_won(maximising_player)) {
        return 1;
    } else if (b.has_won(other_player(maximising_player))) {
        return -1;
    } else if (depth <= 0 || !b.has_empty_cell()) {
        return 0;
    }

    if (current_player == maximising_player) {
        int maxvalue = -2;
        Point best_move;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (b.get_cell(y, x) == CellState::EMPTY) {
                    b.play_chip(y, x, current_player);
                    int value = minimaxab(b, maximising_player, other_player(current_player),
                                          depth - 1, move, false, alpha, beta);
                    b.clear_cell(y, x);

                    if (value > maxvalue) {
                        maxvalue = value;
                        best_move.y = y;
                        best_move.x = x;
                    }
                    if (value > alpha) {
                        alpha = value;
                    }
                    if (alpha >= beta) {
                        break;
                    }
                }
            }
        }
        if (first_move) {
            move = best_move;
        }
        return maxvalue;
    } else {
        int minvalue = 2;
        Point best_move;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (b.get_cell(y, x) == CellState::EMPTY) {
                    b.play_chip(y, x, current_player);
                    int value = minimaxab(b, maximising_player, other_player(current_player),
                                          depth - 1, move, false, alpha, beta);
                    b.clear_cell(y, x);

                    if (value < minvalue) {
                        minvalue = value;
                        best_move.y = y;
                        best_move.x = x;
                    }
                    if (value < beta) {
                        beta = value;
                    }
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        if (first_move) {
            move = best_move;
        }
        return minvalue;
    }
}

bool find_best_move1(Board &b, Chip player, Point &move) {
    Point *p = nullptr;
    minimax(b, player, player, 10, p, true);
    if (!p) {
        return false;
    } else {
        move = *p; // copy constructor
        delete (p);
        return true;
    }
}

bool find_best_move2(Board &b, Chip player, Point &move) {
    std::unique_ptr<Point> p;
    minimax2(b, player, player, 10, p, true);
    if (!p) {
        return false;
    } else {
        move = *p;
        return true;
    }
}

bool find_best_move3(Board &b, Chip player, Point &move) {
    if (b.has_won(player) ||
        b.has_won(other_player(player)) ||
        !b.has_empty_cell()) {
        return false;
    }
    minimax3(b, player, player, 10, move, true);
    return true;
}

bool find_best_move4(Board &b, Chip player, Point &move) {
    if (b.has_won(player) ||
        b.has_won(other_player(player)) ||
        !b.has_empty_cell()) {
        return false;
    }
    negamax(b, player, 10, move, true);
    return true;
}

bool find_best_move5(Board &b, Chip player, Point &move) {
    if (b.has_won(player) ||
        b.has_won(other_player(player)) ||
        !b.has_empty_cell()) {
        return false;
    }
    negamaxab(b, player, 10, move, true, -2, 2);
//    minimaxab(b, player, player, 10, move, true, -2, 2);
    return true;
}

bool find_best_move(Board &b, Chip player, Point &move) {
    return find_best_move5(b, player, move);
}
