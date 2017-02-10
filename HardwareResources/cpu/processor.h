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

enum _instructionFormat {R_TYPE, I_TYPE, J_TYPE};
enum _instructionType {
	ADD, ADDI, ADDIU, ADDU, AND, ANDI, 
	BEQ, BND, DIV, J, JAL, JR, LB, LUI,
	LW, NOP, OR, ORI, SB, SLL, SLLV, SLT,
	SRL
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

void executeInstruction(uint32_t instruction);

instructionFormat getInstructionFormat(uint32_t instruction);
instructionType getInstructioType(uint32_t instruction);

#endif