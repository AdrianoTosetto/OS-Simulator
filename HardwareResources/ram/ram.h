/*
* ram org: 0x12345678
*  		   0x78 = byte 0
*  		   0x55 = byte 1 and so on
* everything is treated in hex format
*  
*/

#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
	This is a 512MB ram, 4 bytes per line(or 1 word per line), so
	is has 4 columns(4 bytes) and 2^7 * 2^10 rows 
	
*/
uint32_t ramCols = 4;
uint32_t ramRows = (128 * 1024);

typedef uint32_t ramAddress;

uint8_t ramMatrix[128 * 1024][4];

typedef struct _ram ram;

struct _ram {
	uint8_t ramMatrix[128 * 1024][4];
};

void writeByte(ram *r, ramAddress addr, uint8_t data);
void writeWord(ram *r, ramAddress addr, uint32_t data);
void writeHal(ram *r, ramAddress addr, uint16_t data);

uint32_t readWord(ram *r, ramAddress addr);
uint16_t readHalf(ram *r, ramAddress addr);
uint8_t readByte(ram *r, ramAddress addr);

uint32_t concatenate(uint32_t x, uint32_t y);

#endif