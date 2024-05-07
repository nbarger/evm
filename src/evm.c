#include "evm.h"
#include "instr.h"

// creates a new evm instance
EVMInstance* evmNew()
{
	EVMInstance* e = malloc(sizeof(EVMInstance));

	e->pc = 0;
	e->dsp = 0;
	e->rsp = 0;

	e->flags = 0;

	e->registers = calloc(REG_AMOUNT, sizeof(uint8_t));

	e->codeMem = malloc(CODE_MAX);
	e->dataStack = malloc(DATA_STACK_MAX);
	e->returnStack = malloc(RETURN_STACK_MAX);

	e->running = 0;

	return e;
}

// frees the data of the instance
void evmEnd(EVMInstance* e)
{
	free(e->registers);

	free(e->codeMem);
	free(e->dataStack);
	free(e->returnStack);

	free(e);
}

// starts an instance (must be updated manually using evmCycle)
void evmStart(EVMInstance* e, size_t start)
{
	e->pc = start;
}

void evmExecuteInstr(EVMInstance* e, uint8_t instr)
{
	opTable[instr](e);
}

void evmCycle(EVMInstance* e)
{
	uint8_t instr;

	// fetch instruction
	instr = e->codeMem[e->pc];
	// execute
	evmExecuteInstr(e, instr);
}

void evmLoadCode(EVMInstance* e, size_t start, uint8_t* code, size_t codeSize)
{
	memcpy(e->codeMem+start, code, codeSize);
}

void evmReturnStackWrite(EVMInstance* e, size_t addr, uint8_t data)
{
	e->returnStack[addr] = data;
}

uint8_t evmReturnStackRead(EVMInstance* e, size_t addr)
{
	return e->returnStack[addr];
}

void evmDataStackWrite(EVMInstance* e, size_t addr, uint8_t data)
{
	e->dataStack[addr] = data;
}
