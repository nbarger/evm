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

	e->instr = 0;

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
	e->running = 1;
}

void evmExecuteInstr(EVMInstance* e, uint8_t instr)
{
	opTable[instr](e);
}

void evmCycle(EVMInstance* e)
{
	// fetch instruction
	e->instr = e->codeMem[e->pc];
	// execute
	evmExecuteInstr(e, e->instr);
}

void evmMonitor(EVMInstance* e)
{
	size_t i;

	// pointer regs
	printf("PC   DSP  RSP\n");
	printf("%04d %04d %04d\n", (int)e->pc, (int)e->dsp, (int)e->rsp);
	printf("Flags: %x\n", e->flags);
	printf("r1 r2 r3 r4\n");
	for (i=0; i<4; i++)
		printf("%02x ", e->registers[i]);
	printf("\nr5 r6 lo hi\n");
	for (i=4; i<8; i++)
		printf("%02x ", e->registers[i]);
	printf("\nCurrent instruction: %02x\n\n", e->instr);
}

void evmDataDump(EVMInstance* e)
{
	size_t i;
	
	// print data
	printf("{\n");
	for (i=0; i<DATA_STACK_MAX; i+=4)
	{
		printf("    %02x | %c |    %02x | %c |    ", e->dataStack[i], e->dataStack[i], 
				e->dataStack[i+1], e->dataStack[i+1]);
		printf("    %02x | %c |    %02x | %c |\n", e->dataStack[i+2], e->dataStack[i+2],
				e->dataStack[i+3], e->dataStack[i+3]);
	}
	printf("\n}\n");
}

void evmCodeDump(EVMInstance* e)
{
	size_t i;
	
	// print code
	printf("{\n");
	for (i=0; i<CODE_MAX; i+=4)
	{
		printf("    %02x | %c |    %02x | %c |    ", e->codeMem[i], e->codeMem[i], 
				e->codeMem[i+1], e->codeMem[i+1]);
		printf("    %02x | %c |    %02x | %c |\n", e->codeMem[i+2], e->codeMem[i+2],
				e->codeMem[i+3], e->codeMem[i+3]);
	}
	printf("\n}\n");
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
