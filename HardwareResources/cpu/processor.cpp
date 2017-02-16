#include "processor.h"
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <bitset>

instructionFormat Processor::getInstructionFormat (uint32_t instruction) {
	uint8_t opcode = (instruction & 0xFC000000) >> 26;
	if(opcode == 0x00000000) 
		return R_TYPE;
	else if(opcode == 0x00000002 || opcode == 0x00000003 || opcode == 0x0000001A)
		return J_TYPE;
	else
		return I_TYPE;
}
instructionType Processor::getInstructioType(uint32_t instruction) {
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


uint32_t Processor::getOpcode(uint32_t instruction) {
	return (instruction & 0xFC000000) >> 26;
}
uint32_t Processor::getRS(uint32_t instruction) {
	return (instruction & 0x03D00000) >> 21;
}
uint32_t Processor::getRT(uint32_t instruction) {
	return (instruction & 0x001F0000) >> 16; //1111 11 11 111 1 1111 1111
}
uint32_t Processor::getRD(uint32_t instruction) {
	return (instruction & 0x0000F800) >> 11;
}
uint32_t Processor::getInstrConstant(uint32_t instruction){
	return (instruction & 0x0000FFFF);
}
uint32_t Processor::getFunct(uint32_t instruction) {
	return (instruction & 0x0000003F);
}
uint32_t Processor::getShamt(uint32_t instruction) {
	return (instruction & 0x000007C0) >> 6;
}

/*
* Mips uses the funct field to differentiate the R-type instructions. 
*
*/
instructionType Processor::getInstructioTypeFormatR(uint32_t instruction) {
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
instructionType Processor::getInstructioTypeFormatI(uint32_t instruction){}
instructionType Processor::getInstructioTypeFormatJ(uint32_t instruction){}

void Processor::writeRegister(uint8_t reg, uint32_t value) {
	
	switch(reg) {
		case 0:
			return; // $zero register can not be written
		break;
		case 1:
			return;
		break;
		case 2:
			registers.returnRegisters.$v0 = value;
		break;
		case 3:
			registers.returnRegisters.$v1 = value;
		break;
		case 4:
			registers.argRegisters.$a0 = value;
		break;
		case 5:
			registers.argRegisters.$a1 = value;
		break;
		case 6:
			registers.argRegisters.$a2 = value;
		break;
		case 7:
			registers.argRegisters.$a3 = value;
		break;
		case 8:
			registers.tempRegisters.$t0 = value;
		break;
		case 9:
			registers.tempRegisters.$t1 = value;
		break;
		case 10:
			registers.tempRegisters.$t2 = value;
		break;
		case 11:
			registers.tempRegisters.$t3 = value;
		break;
		case 12:
			registers.tempRegisters.$t4 = value;
		break;
		case 13:
			registers.tempRegisters.$t5 = value;
		break;
		case 14:
			registers.tempRegisters.$t6 = value;
		break;
		case 15:
			registers.tempRegisters.$t7 = value;
		break;
		case 16:
			registers.savedRegisters.$s0 = value;
		break;
		case 17:
			registers.savedRegisters.$s1 = value;
		break;
		case 18:
			registers.savedRegisters.$s2 = value;
		break;
		case 19:
			registers.savedRegisters.$s3 = value;
		break;
		case 20:
			registers.savedRegisters.$s4 = value;
		break;
		case 21:
			registers.savedRegisters.$s5 = value;
		break;
		case 22:
			registers.savedRegisters.$s6 = value;
		break;
		case 23:
			registers.savedRegisters.$s7 = value;
		break;
		case 24:
			registers.tempRegisters.$t8 = value;
		break;
		case 25:
			registers.tempRegisters.$t9 = value;
		break;
		case 26:
			registers.exceptionRegisters.$k0 = value;
		break;
		case 27:
			registers.exceptionRegisters.$k1 = value;
		break;
		case 28:
			registers.$gp = value;
		break;
		case 29:
			registers.$sp = value;
		break;
		case 30:
			registers.$fp = value;
		break;
		case 31:
			registers.$ra = value;
		break;
	}
}

uint32_t Processor::getRegValue(uint8_t reg) {
	
	switch(reg) {
		case 0:
			return registers.$zero; // $zero register can not be written
		break;
		case 1:
			return 0;
		break;
		case 2:
			return registers.returnRegisters.$v0;
		break;
		case 3:
			return registers.returnRegisters.$v1;
		break;
		case 4:
			return registers.argRegisters.$a0;
		break;
		case 5:
			return registers.argRegisters.$a1;
		break;
		case 6:
			return registers.argRegisters.$a2;
		break;
		case 7:
			return registers.argRegisters.$a3 ;
		break;
		case 8:
			return registers.tempRegisters.$t0;
		break;
		case 9:
			return registers.tempRegisters.$t1;
		break;
		case 10:
			return registers.tempRegisters.$t2;
		break;
		case 11:
			return registers.tempRegisters.$t3;
		break;
		case 12:
			return registers.tempRegisters.$t4;
		break;
		case 13:
			return registers.tempRegisters.$t5;
		break;
		case 14:
			return registers.tempRegisters.$t6;
		break;
		case 15:
			return registers.tempRegisters.$t7;
		break;
		case 16:
			return registers.savedRegisters.$s0;
		break;
		case 17:
			return registers.savedRegisters.$s1;
		break;
		case 18:
			return registers.savedRegisters.$s2;
		break;
		case 19:
			return registers.savedRegisters.$s3;
		break;
		case 20:
			return registers.savedRegisters.$s4;
		break;
		case 21:
			return registers.savedRegisters.$s5;
		break;
		case 22:
			return registers.savedRegisters.$s6;
		break;
		case 23:
			return registers.savedRegisters.$s7;
		break;
		case 24:
			return registers.tempRegisters.$t8;
		break;
		case 25:
			return registers.tempRegisters.$t9;
		break;
		case 26:
			return registers.exceptionRegisters.$k0;
		break;
		case 27:
			return registers.exceptionRegisters.$k1;
		break;
		case 28:
			return registers.$gp;
		break;
		case 29:
			return registers.$sp;
		break;
		case 30:
			return registers.$fp;
		break;
		case 31:
			return registers.$ra;
		break;
	}
}


/*
* 
*/
void Processor::incrementPC() {
	registers.$pc = registers.$pc + 4;
}
void Processor::setPC(uint32_t value) {
	registers.$pc = value;
}


void Processor::initProcessor(){}
void Processor::executeInstruction(uint32_t instruction) {
	instructionType type = getInstructioType(instruction);
	uint32_t rd       = getRD(instruction);
	uint32_t rs       = getRS(instruction);
	uint32_t rt       = getRT(instruction);
	uint32_t constVal = getInstrConstant(instruction);

	switch(type) {
		case ADD:
			writeRegister(rd, getRegValue(rs) + getRegValue(rt));
		break;
		case ADDI:
			writeRegister(rt, getRegValue(rs) + constVal);
		break;
		case AND:
			writeRegister(rd, getRegValue(rs) & getRegValue(rt));
		break;
		case ANDI:
			writeRegister(rt, getRegValue(rd) & constVal);
		break;

		case OR:

		break;

		case ORI:

		break;
		default:
		break;
	}
}

int main(int argc, char const *argv[])
{
	Processor *p = new Processor;
	memset(p,0, sizeof(p));
	p->executeInstruction(0b00100001000010000000000000000111);
	p->executeInstruction(0b00100001010010100000000000001011);
	p->executeInstruction(0b00000001000010100101100000100100);
	std::cout << p->registers.tempRegisters.$t0 << std::endl;
	std::cout << p->registers.tempRegisters.$t2 << std::endl;
	
	std::cout << std::bitset<32>(p->registers.tempRegisters.$t3) << std::endl;
	return 0;
}