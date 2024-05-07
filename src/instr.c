#include "instr.h"

OpTable opTable[] =
{
    &opHalt
};

void opHalt(EVMInstance* e)
{
    e->running = 0;
}
