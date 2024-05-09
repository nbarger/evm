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
	&opRightShiftRegister,
	&opCompare,
	&opJumpIfEqual,
	&opJumpIfNotEqual,
	&opJumpIfGreater,
	&opJumpIfLess
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
	e->pc++;
	e->dataDataStack[
		B8TO16(e->dataStack[B8TO16(e->registers[6], e->registers[7])],
				e->dataStack[B8TO16(e->registers[6],
					e->registers[7])+1])+registers[5]] =
			e->registers[e->codeMem[e->pc]];
	e->pc++;
}

// store register at an address referenced at hilo with a direct offset of r5 (so (hilo),r5)
void opStoreIndirectOffset(EVMInstance* e)
{
	e->pc++;
	e->dataDataStack[
		B8TO16(e->dataStack[B8TO16(e->registers[6], e->registers[7])+e->registers[5]],
				e->dataStack[B8TO16(e->registers[6],
					e->registers[7])+1+e->registers[5]])] =
			e->registers[e->codeMem[e->pc]];
	e->pc++;
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

// adds two registers together and stores it in register a
void opAddRegisters(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->registers[e->codeMem[e->pc]]+e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

// subtracts register a by register b
void opSubtractRegisters(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->registers[e->codeMem[e->pc]]-e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

// multiplies register a by register b
void opMultiplyRegisters(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->registers[e->codeMem[e->pc]]*e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

// divides register a by register b, also storing the remainder in reg b
void opDivideRegisters(EVMInstance* e)
{
	e->pc++;
	if (e->registers[e->codeMem[e->pc+1]] == 0)
	{
		fprintf(stderr, "Cannot divide by zero; insert traceback i guess\n");
		e->running = 0;
		return;
	}
	e->registers[e->codeMem[e->pc]] = (uint8_t)
		e->registers[e->codeMem[e->pc]]/e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

// bitwise ands register a by register b
void opAndRegisters(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->registers[e->codeMem[e->pc]]&e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

// bitwise ors register a by register b
void opOrRegisters(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->registers[e->codeMem[e->pc]]|e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

// bitwise xors register a by register b
void opXOrRegisters(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->registers[e->codeMem[e->pc]]^e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

// nots register a
void opNotRegister(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		~e->registers[e->codeMem[e->pc]];
	e->pc += 1;
}

// leftshifts register a by register b
void opLeftShiftRegister(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->registers[e->codeMem[e->pc]]<<e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

// rightshifts register b by register b
void opRightShiftRegister(EVMInstance* e)
{
	e->pc++;
	e->registers[e->codeMem[e->pc]] = 
		e->registers[e->codeMem[e->pc]]>>e->registers[e->codeMem[e->pc+1]];
	e->pc += 2;
}

/*
 * Flags:
 *      RGE
 * 00000000
 */

// compare a with b, setting any flags
void opCompare(EVMInstance* e)
{
	e->pc++;
	if (e->registers
}

// jump if the equal flag is set
void opJumpIfEqual(EVMInstance* e)
{

}

// jump if the equal flag is not set
void opJumpIfNotEqual(EVMInstance* e)
{

}

// jump if the greater flag is set
void opJumpIfGreater(EVMInstance* e)
{

}

// jump if the greater flag is not set
void opJumpIfLess(EVMInstance* e)
{

}
