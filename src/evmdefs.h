#ifndef EVMDEFS_H
#define EVMDEFS_H

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
	size_t pc;
	size_t dsp;
	size_t rsp;

	uint8_t flags;

	uint8_t* registers;

	uint8_t* codeMem;
	uint8_t* dataStack;
	uint8_t* returnStack;

	uint8_t instr;

	int running;
}EVMInstance;

#endif
