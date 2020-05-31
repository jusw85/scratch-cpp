/*
 * functions.h
 *
 *  Created on: 15/09/2010
 *      Author: WCHOONTE
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "SDL/SDL.h"

bool Init();
bool LoadFiles();
void CleanUp();

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#endif /* FUNCTIONS_H_ */
