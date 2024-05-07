#ifndef INSTR_H
#define INSTR_H

#include "evmdefs.h"

#define NUM_INSTR 3

void opHalt(EVMInstance* e);
void opNop(EVMInstance* e);
void opLoadImmediate(EVMInstance* e);

typedef void (*OpTable)(EVMInstance*);

extern OpTable opTable[NUM_INSTR];

#endif
