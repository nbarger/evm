#include "instr.h"

// holy moly that's a lot of instructions
OpTable opTable[] =
{
	&opHalt,
	&opNop,
	&opLoadImmediate,
	&opTransferRegister,
	&opLoadData,
	&opStoreRegister,
	&opStoreIndirect,
	&opStoreIndirectOffset,
	&opPushRegister,
	&opPopRegister,
	&opJump,
	&opNewSubroutine,
	&opReturnSubroutine,
	&opIncrementRegister,
	&opDecrementRegister,
	&opAddRegisters,
	&opSubtractRegisters,
	&opMultiplyRegisters,
	&opDivideRegisters,
	&opAndRegisters,
	&opOrRegisters,
	&opXOrRegisters,
	&opNotRegister,
	&opLeftShiftRegister,
	&opRightShiftRegister
};

// set the running flag to 0, halting the process
void opHalt(EVMInstance* e)
{
	e->running = 0;
}

// perform no operation
void opNop(EVMInstance* e)
{
	e->pc++;
}

// load register "a" with value "b"
void opLoadImmediate(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = e->codeMem[e->pc+1];
	e->pc += 2;
}

// transfers register b to register a
void opTransferRegister(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = e->codeMem[e->pc+1];
	e->pc += 2;
}

// load value from data stack into register a from hilo, with an offset of r5
void opLoadData(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->dataStack[B8TO16(e->registers[6], e->registers[7])+e->registers[5]];
}

// store register "a" at address hilo with offset r5
void opStoreRegister(EVMInstance* e)
{
	e->pc++;
	e->dataStack[B8TO16(e->registers[6], e->registers[7])+e->registers[5]] =
		e->registers[e->codeMem[e->pc]];
	e->pc++;
}

// store register at an address referenced at hilo with an indirect offset of r5 (so (hilo,r5))
void opStoreIndirect(EVMInstance* e)
{
	//TODO
}

// store register at an address referenced at hilo with a direct offset of r5 (so (hilo),r5)
void opStoreIndirectOffset(EVMInstance* e)
{
	//TODO
}

// push register "a" on stack
void opPushRegister(EVMInstance* e)
{
	e->pc++;
	e->dataStack[e->dsp] = e->registers[e->codeMem[e->pc]];
	e->dsp++;
	e->pc++;
}

// pop stack to register
void opPopRegister(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = e->dataStack[e->dsp-1];
	e->dsp--;
	e->pc++;
}

// jump to address hilo
void opJump(EVMInstance* e)
{
	e->pc = B8TO16(e->registers[6], e->registers[7]);
}

// create a new subroutine and jump to it
void opNewSubroutine(EVMInstance* e)
{
	e->returnStack[e->rsp] = GETLO(e->pc);
	e->returnStack[e->rsp+1] = GETHI(e->pc);
	e->pc = B8TO16(e->registers[6], e->registers[7]);
	e->rsp += 2;
}

// loads the return stack onto hilo
void opReturnSubroutine(EVMInstance* e)
{
	e->pc++;
	e->registers[6] = e->returnStack[e->dsp-2];
	e->registers[7] = e->returnStack[e->dsp-1];
	e->rsp -= 2;
}

// increments a register
void opIncrementRegister(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]]++;
	e->pc++;
}

// decrements a register
void opDecrementRegister(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]]--;
	e->pc++;
}

// adds two registers together
void opAddRegisters(EVMInstance* e)
{

}

// subtracts register a by register b
void opSubtractRegisters(EVMInstance* e)
{

}

// multiplies register a by register b
void opMultiplyRegisters(EVMInstance* e)
{

}

// divides register a by register b
void opDivideRegisters(EVMInstance* e)
{

}

// bitwise ands register a by register b
void opAndRegisters(EVMInstance* e)
{

}

// bitwise ors register a by register b
void opOrRegisters(EVMInstance* e)
{

}

// bitwise xors register a by register b
void opXOrRegisters(EVMInstance* e)
{

}

// nots register a
void opNotRegister(EVMInstance* e)
{

}

// leftshifts register a by register b
void opLeftShiftRegister(EVMInstance* e)
{

}

// rightshifts register b by register b
void opRightShiftRegister(EVMInstance* e)
{

}
