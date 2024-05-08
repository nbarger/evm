#ifndef INSTR_H
#define INSTR_H

#include "evmdefs.h"

#define NUM_INSTR 25

void opHalt(EVMInstance* e); // 0
void opNop(EVMInstance* e); // 1
void opLoadImmediate(EVMInstance* e); // 2
void opTransferRegister(EVMInstance* e); // 3
void opLoadData(EVMInstance* e); // 4
void opStoreRegister(EVMInstance* e); // 5
void opStoreIndirect(EVMInstance* e); // 6
void opStoreIndirectOffset(EVMInstance* e); // 7
void opPushRegister(EVMInstance* e); // 8
void opPopRegister(EVMInstance* e); // 9
void opJump(EVMInstance* e); // 10
void opNewSubroutine(EVMInstance* e); // 11
void opReturnSubroutine(EVMInstance* e); // 12
void opIncrementRegister(EVMInstance* e); // 13
void opDecrementRegister(EVMInstance* e); // 14
void opAddRegisters(EVMInstance* e); // 15
void opSubtractRegisters(EVMInstance* e); // 16
void opMultiplyRegisters(EVMInstance* e); // 17
void opDivideRegisters(EVMInstance* e); // 18
void opAndRegisters(EVMInstance* e); // 19
void opOrRegisters(EVMInstance* e); // 20
void opXOrRegisters(EVMInstance* e); // 21
void opNotRegister(EVMInstance* e); // 22
void opLeftShiftRegister(EVMInstance* e); // 23
void opRightShiftRegister(EVMInstance* e); // 24

typedef void (*OpTable)(EVMInstance*);

extern OpTable opTable[NUM_INSTR];

#endif
