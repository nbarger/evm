#ifndef INSTR_H
#define INSTR_H

#include "evmdefs.h"

#define NUM_INSTR 30

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
void opJump(EVMInstance* e); // a
void opNewSubroutine(EVMInstance* e); // b
void opReturnSubroutine(EVMInstance* e); // c
void opIncrementRegister(EVMInstance* e); // d
void opDecrementRegister(EVMInstance* e); // e
void opAddRegisters(EVMInstance* e); // f
void opSubtractRegisters(EVMInstance* e); // 10
void opMultiplyRegisters(EVMInstance* e); // 11
void opDivideRegisters(EVMInstance* e); // 12
void opAndRegisters(EVMInstance* e); // 13
void opOrRegisters(EVMInstance* e); // 14
void opXOrRegisters(EVMInstance* e); // 15
void opNotRegister(EVMInstance* e); // 16
void opLeftShiftRegister(EVMInstance* e); // 17
void opRightShiftRegister(EVMInstance* e); // 18
void opCompare(EVMInstance* e); // 19
void opJumpIfEqual(EVMInstance* e); // 1a
void opJumpIfNotEqual(EVMInstance* e); // 1b
void opJumpIfGreater(EVMInstance* e); // 1c
void opJumpIfLess(EVMInstance* e); // 1d

typedef void (*OpTable)(EVMInstance*);

extern OpTable opTable[NUM_INSTR];

#endif
