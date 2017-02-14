#include "processor.h"

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
			return getInstructioTypeFormatR(instruction);
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
uint32_t getRD(uint32_t instruction) {
	return (instruction & 0x0000F800) >> 11;
}
uint32_t getInstrConstant(uint32_t instruction){
	return (instruction & 0x0000FFFF);
}
uint32_t getFunct(uint32_t instruction) {
	return (instruction & 0x0000003F);
}
uint32_t getShamt(uint32_t instruction) {
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

void writeRegister(uint8_t reg, uint32_t value, processor *p) {
	if(p == NULL) return;
	switch(reg) {
		case 0:
			return; // $zero register can not be written
		break;
		case 1:
			return;
		break;
		case 2:
			p->registers.returnRegisters.$v0 = value;
			printf("%d\n",p->registers.returnRegisters.$v0);
		break;
		case 3:
			p->registers.returnRegisters.$v1 = value;
		break;
		case 4:
			p->registers.argRegisters.$a0 = value;
		break;
		case 5:
			p->registers.argRegisters.$a1 = value;
		break;
		case 6:
			p->registers.argRegisters.$a2 = value;
		break;
		case 7:
			p->registers.argRegisters.$a3 = value;
		break;
		case 8:
			p->registers.tempRegisters.$t0 = value;
		break;
		case 9:
			p->registers.tempRegisters.$t1 = value;
		break;
		case 10:
			p->registers.tempRegisters.$t2 = value;
		break;
		case 11:
			p->registers.tempRegisters.$t3 = value;
		break;
		case 12:
			p->registers.tempRegisters.$t4 = value;
		break;
		case 13:
			p->registers.tempRegisters.$t5 = value;
		break;
		case 14:
			p->registers.tempRegisters.$t6 = value;
		break;
		case 15:
			p->registers.tempRegisters.$t7 = value;
		break;
		case 16:
			p->registers.savedRegisters.$s0 = value;
		break;
		case 17:
			p->registers.savedRegisters.$s1 = value;
		break;
		case 18:
			p->registers.savedRegisters.$s2 = value;
		break;
		case 19:
			p->registers.savedRegisters.$s3 = value;
		break;
		case 20:
			p->registers.savedRegisters.$s4 = value;
		break;
		case 21:
			p->registers.savedRegisters.$s5 = value;
		break;
		case 22:
			p->registers.savedRegisters.$s6 = value;
		break;
		case 23:
			p->registers.savedRegisters.$s7 = value;
		break;
		case 24:
			p->registers.tempRegisters.$t8 = value;
		break;
		case 25:
			p->registers.tempRegisters.$t9 = value;
		break;
		case 26:
			p->registers.exceptionRegisters.$k0 = value;
		break;
		case 27:
			p->registers.exceptionRegisters.$k1 = value;
		break;
		case 28:
			p->registers.$gp = value;
		break;
		case 29:
			p->registers.$sp = value;
		break;
		case 30:
			p->registers.$fp = value;
		break;
		case 31:
			p->registers.$ra = value;
		break;
	}
}

/*
* 
*/
void incrementPC(processor *p) {
	p->registers.$pc = p->registers.$pc + 4;
}
void setPC(processor *p, uint32_t value) {
	p->registers.$pc = value;
}


void initProcessor();
void executeInstruction(Processor *p, uint32_t instruction) {
	instructionType type = getInstructioType(instruction);

}

int main(int argc, char const *argv[])
{
	processor p;
	writeRegister(2,0x1,&p);
	printf("%d\n", p.registers.returnRegisters.$v0);
	return 0;
}