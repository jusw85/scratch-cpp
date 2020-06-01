/*
 * constants.h
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#ifndef SCRATCH_CONSTANTS_H
#define SCRATCH_CONSTANTS_H

#include <string>

const std::string APP_NAME = "Connect 4";
const std::string DATA_PATH = "../data/";

const int SCREEN_BPP = 32;
const int CELL_WIDTH = 32;
const int CELL_HEIGHT = 32;
const int GRID_WIDTH = 5;
const int GRID_HEIGHT = 4;
//const int GRID_WIDTH = 7;
//const int GRID_HEIGHT = 6;
const int SCREEN_WIDTH = CELL_WIDTH * GRID_WIDTH;
const int SCREEN_HEIGHT = CELL_HEIGHT * GRID_HEIGHT;

const int GRID_COLOUR[] = {64, 189, 214};
const int GRID_HILITE_COLOUR[] = {53, 151, 171};

#endif
