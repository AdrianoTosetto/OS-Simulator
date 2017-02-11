#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdint.h>
#include "../ram/ram.h"

typedef struct _procRegisters procRegisters_t;
typedef struct _tempRegisters tempRegisters_t;
typedef struct _savedRegisters savedRegisters_t;
typedef struct _returnRegisters returnRegisters_t;
typedef struct _exceptionRegisters exceptionRegisters_t;


typedef enum _instructionFormat instructionFormat;
typedef enum _instructionType instructionType;

enum _instructionFormat {R_TYPE=1, I_TYPE=2, J_TYPE=3};
enum _instructionType {
	ADD=1, ADDI=2, ADDIU=3, ADDU=4, AND=5, ANDI=6, 
	BEQ=7, BNE=8, DIV=9, DIVU=10, J=11, JAL=12, JR=13, LBU=14,
	LHU=15, LUI=16, LW=17, MFHI=18, MFL0=19, MFC0=20, MULT=21,
	MULTU=22, NOR=23, XOR=24, OR=25, ORI=26, SB=27, SH=28, SLT=29,
	SLTI=30, SLTIU=31, SLTU=32, SLL=33, SRL=34, SRA=35, SUB=36,
	SUBU=37, SW=38, _WHAT_ = 40
};

struct _tempRegisters {
	uint32_t $t0;
	uint32_t $t1;
	uint32_t $t2;
	uint32_t $t3;
	uint32_t $t4;
	uint32_t $t5;
	uint32_t $t6;
	uint32_t $t7;
	uint32_t $t8;
	uint32_t $t9;
};
struct _savedRegisters{
	uint32_t $s0;
	uint32_t $s1;
	uint32_t $s2;
	uint32_t $s3;
	uint32_t $s4;
	uint32_t $s5;
	uint32_t $s6;
	uint32_t $s7;
};

/*
* register used to function return values
*/
struct _returnRegisters{
	uint32_t $v0;
	uint32_t $v1;
};
/*
* registers used to store argument for functions
*/
struct _argRegisters{
	uint32_t $a0;
	uint32_t $a1;
	uint32_t $a2;
	uint32_t $a3;
};
/*
* exceptions registers
*/
struct _exceptionRegisters{
	uint32_t $k0;
	uint32_t $k1;
};


struct _procRegisters {
	tempRegisters_t tempRegisters;
	savedRegisters_t savedRegisters;
	returnRegisters_t returnRegisters;
	exceptionRegisters_t exceptionRegisters; 
	
	uint32_t $zero; // 0
	uint32_t $at;  // 1

	uint32_t $gp; //global pointer
	uint32_t $sp; //stack pointer
	uint32_t $fp; //frame pointer
	uint32_t $ra; //return address
	uint32_t $pc;
};

struct _processor {
	procRegisters_t registers;
	long long clockPeriod;
};


void executeInstruction(uint32_t instruction);

instructionFormat getInstructionFormat(uint32_t instruction);
instructionType getInstructioType(uint32_t instruction);
uint32_t getOpcode(uint32_t instruction);
uint32_t getRT(uint32_t instruction);
uint32_t getRD(uint32_t instruction);
uint32_t getRS(uint32_t instruction);
uint32_t getInstrConstant(uint32_t instruction);
uint32_t getFunct(uint32_t instruction);
uint32_t getShamt(uint32_t instruction);

instructionType getInstructioTypeFormatR(uint32_t instruction);
instructionType getInstructioTypeFormatI(uint32_t instruction);
instructionType getInstructioTypeFormatJ(uint32_t instruction);



#endif