#include "processor.h"

void executeInstruction(uint32_t instruction);

instructionFormat getInstructionFormat(uint32_t instruction) {
	uint8_t opcode = (instruction & 0xFC000000) >> 26;
	if(opcode == 0x00000000) 
		return R_TYPE;
	else if(opcode == 0x00000002 || opcode == 0x00000003 || opcode == 0x0000001A)
		return J_TYPE;
	else
		return I_TYPE;
}
instructionType getInstructioType(uint32_t instruction) {
	instructionFormat t = getInstructionFormat(instruction);

	switch(t) {
		case R_TYPE:

		break;
		case J_TYPE:

		break;
		case I_TYPE:

		break;
	}
}


uint32_t getOpcode(uint32_t instruction){}
uint32_t getRT(uint32_t instruction){}
uint32_t getRD(uint32_t instruction){}
uint32_t getRS(uint32_t instruction){}
uint32_t getInstrConstant(uint32_t instruction){}
uint32_t getFunct(uint32_t instruction){}
uint32_t getShamt(uint32_t instruction){}

int main(int argc, char const *argv[])
{
	printf("%d\n",getInstructionFormat(0x00622020));
	printf("%d\n", getInstructionFormat(0b10001100110001010000000000001000));
	return 0;
}