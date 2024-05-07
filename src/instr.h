#ifndef INSTR_H
#define INSTR_H

#include "evmdefs.h"

#define NUM_INSTR 1

void opHalt(EVMInstance* e);

typedef void (*OpTable)(EVMInstance*);

OpTable opTable[NUM_INSTR];

#endif
