#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdint.h>
#include "../ram/ram.h"

typedef struct _procRegisters procRegisters_t;
typedef struct _tempRegisters tempRegisters_t;
typedef struct _savedRegisters savedRegisters_t;
typedef struct _argRegisters argRegisters_t;
typedef struct _returnRegisters returnRegisters_t;
typedef struct _exceptionRegisters exceptionRegisters_t;
typedef struct _processor processor;


enum _instructionFormat {R_TYPE=1, I_TYPE=2, J_TYPE=3};
enum _instructionType {
	ADD=1, ADDI=2, ADDIU=3, ADDU=4, AND=5, ANDI=6, 
	BEQ=7, BNE=8, DIV=9, DIVU=10, J=11, JAL=12, JR=13, LBU=14,
	LHU=15, LUI=16, LW=17, MFHI=18, MFL0=19, MFC0=20, MULT=21,
	MULTU=22, NOR=23, XOR=24, OR=25, ORI=26, SB=27, SH=28, SLT=29,
	SLTI=30, SLTIU=31, SLTU=32, SLL=33, SRL=34, SRA=35, SUB=36,
	SUBU=37, SW=38, _WHAT_ = 40
};


typedef enum _instructionFormat instructionFormat;
typedef enum _instructionType instructionType;

struct _tempRegisters {
	uint32_t $t0; //8
	uint32_t $t1; //9
	uint32_t $t2; //10
	uint32_t $t3; //11
	uint32_t $t4; //12
	uint32_t $t5; //13
	uint32_t $t6; //14
	uint32_t $t7; //15
	uint32_t $t8; //24
	uint32_t $t9; //25
};
struct _savedRegisters{
	uint32_t $s0; //16
	uint32_t $s1; //17
	uint32_t $s2; //18
	uint32_t $s3; //19
	uint32_t $s4; //20
	uint32_t $s5; //21
	uint32_t $s6; //22
	uint32_t $s7; //23
};

/*
* register used to function return values
*/
struct _returnRegisters{
	uint32_t $v0; //2
	uint32_t $v1; //3
};
/*
* registers used to store argument for functions
*/
struct _argRegisters{
	uint32_t $a0; //4
	uint32_t $a1; //5
	uint32_t $a2; //6
	uint32_t $a3; //7
};
/*
* exceptions registers
*/
struct _exceptionRegisters{
	uint32_t $k0; //26
	uint32_t $k1; //27
};


struct _procRegisters {
	tempRegisters_t tempRegisters;
	savedRegisters_t savedRegisters;
	returnRegisters_t returnRegisters;
	exceptionRegisters_t exceptionRegisters;
	argRegisters_t argRegisters;
	
	uint32_t $zero; // 0
	uint32_t $at;  // 1

	uint32_t $gp; //global pointer 28
	uint32_t $sp; //stack pointer 29
	uint32_t $fp; //frame pointer 30
	uint32_t $ra; //return address 31
	uint32_t $pc; //not visible for programmers
};

struct _processor {
	procRegisters_t registers;
	long long clockPeriod;
};

class Processor {
	public: procRegisters_t registers; 

	public: void executeInstruction(uint32_t instruction);
	public: instructionFormat getInstructionFormat(uint32_t instruction);
	public: instructionType getInstructioType(uint32_t instruction);
	public: uint32_t getOpcode(uint32_t instruction);
	public: uint32_t getRT(uint32_t instruction);
	public: uint32_t getRD(uint32_t instruction);
	public: uint32_t getRS(uint32_t instruction);
	public: uint32_t getInstrConstant(uint32_t instruction);
	public: uint32_t getFunct(uint32_t instruction);
	public: uint32_t getShamt(uint32_t instruction);

	public: instructionType getInstructioTypeFormatR(uint32_t instruction);
	public: instructionType getInstructioTypeFormatI(uint32_t instruction);
	public: instructionType getInstructioTypeFormatJ(uint32_t instruction);

	public: void initProcessor();
	public: void writeRegister(uint8_t reg, uint32_t value);
	public: void incrementPC();
	public: void setPC(uint32_t value);
	public: uint32_t getRegValue(uint8_t regNum);


};


#endif