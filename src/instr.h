#ifndef INSTR_H
#define INSTR_H

#include "evmdefs.h"

#define NUM_INSTR 22

void opHalt(EVMInstance* e);
void opNop(EVMInstance* e);
void opLoadImmediate(EVMInstance* e);
void opTransferRegister(EVMInstance* e);
void opLoadData(EVMInstance* e);
void opStoreRegister(EVMInstance* e);
void opStoreIndirect(EVMInstance* e);
void opStoreIndirectOffset(EVMInstance* e);
void opPushRegister(EVMInstance* e);
void opPopRegister(EVMInstance* e);
void opJump(EVMInstance* e);
void opNewSubroutine(EVMInstance* e);
void opReturnSubroutine(EVMInstance* e);
void opIncrementRegister(EVMInstance* e);
void opDecrementRegister(EVMInstance* e);
void opAddRegisters(EVMInstance* e);
void opSubtractRegisters(EVMInstance* e);
void opMultiplyRegisters(EVMInstance* e);
void opDivideRegisters(EVMInstance* e);
void opAndRegisters(EVMInstance* e);
void opOrRegisters(EVMInstance* e);
void opXOrRegisters(EVMInstance* e);
void opNotRegister(EVMInstance* e);
void opLeftShiftRegister(EVMInstance* e);
void opRightShiftRegister(EVMInstance* e);

typedef void (*OpTable)(EVMInstance*);

extern OpTable opTable[NUM_INSTR];

#endif
