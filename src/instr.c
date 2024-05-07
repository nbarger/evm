#include "instr.h"

void executeInstr(EVMInstance* e, uint8_t instr)
{
    opTable[instr](e);
}

void opHalt(EVMInstance* e)
{
    e->running = 0;
}
