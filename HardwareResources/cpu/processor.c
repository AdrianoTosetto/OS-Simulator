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
	instructionFormat f = getInstructionFormat(instruction);

	switch(f) {
		case R_TYPE:
			
		break;
		case J_TYPE:

		break;
		case I_TYPE:

		break;
	}
}


uint32_t getOpcode(uint32_t instruction) {
	return (instruction & 0xFC000000) >> 26;
}
uint32_t getRS(uint32_t instruction) {

	return (instruction & 0x03D00000) >> 21;
}
uint32_t getRT(uint32_t instruction) {
	return (instruction & 0x001F0000) >> 16; //1111 11 11 111 1 1111 1111
}
uint32_t getRD(uint32_t instruction){
	return (instruction & 0x0000F800) >> 11;
}
uint32_t getInstrConstant(uint32_t instruction){
	return (instruction & 0x0000FFFF);
}
uint32_t getFunct(uint32_t instruction){
	return (instruction & 0x0000003F);
}
uint32_t getShamt(uint32_t instruction){
	return (instruction & 0x000007C0) >> 6;
}

/*
* Mips uses the funct field to differentiate the R-type instructions. 
*
*/
instructionType getInstructioTypeFormatR(uint32_t instruction) {
	uint32_t functField = getFunct(instruction);
	switch(functField) {
		case 0x20:
			return ADD;
		break;
		case 0x21:
			return ADDU;
		break;
		case 0x24:
			return AND;
		break;
		case 0x1A:
			return DIV;
		break;
		case 0x1B:
			return DIVU;
		break;
		case 0x08:
			return JR;
		break;
		case 0x18:
			return MULT;
		break;
		case 0x19:
			return MULTU;
		break;
		case 0x27:
			return NOR;
		break;
		case 0x26:
			return XOR;
		break;
		case 0x25:
			return OR;
		break;
		case 0x2A:
			return SLT;
		break;
		case 0x00:
			return SLL;
		break;
		case 0x02:
			return SRL;
		break;
		case 0x22:
			return SUB;
		break;
		case 0x23:
			return SUBU;
		break;
		default:

		return _WHAT_;
	}
}
instructionType getInstructioTypeFormatI(uint32_t instruction);
instructionType getInstructioTypeFormatJ(uint32_t instruction);

int main(int argc, char const *argv[])
{
	printf("%d\n",getInstructioTypeFormatR(0b00000011000000000111100000100000));
	return 0;
}