#ifndef INSTR_H
#define INSTR_H

#include "evmdefs.h"

void executeInstr(EVMInstance* e, uint8_t instr);
void opHalt(EVMInstance* e);

#endif
