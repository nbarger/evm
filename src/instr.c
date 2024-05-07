#include "instr.h"

OpTable opTable[] =
{
    &opHalt,
    &opNop,
    &opLoadImmediate
};

void opHalt(EVMInstance* e)
{
    e->running = 0;
}

void opNop(EVMInstance* e)
{
	e->pc++;
}

void opLoadImmediate(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc++]] = e->codeMem[e->pc++];
}
