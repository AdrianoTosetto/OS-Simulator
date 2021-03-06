#include <stdio.h>
#include "ram.h"

/*
* to support store byte of the proccessor
*
*/

void writeByte(ramAddress addr, uint8_t data) {
	
	uint32_t row = (uint32_t) addr / ramCols;
	uint32_t col = addr % ramCols;

	ramMatrix[row][col] = data;
}
/*
* to support store word of the proccessor
*
*/
void writeWord(ramAddress addr, uint32_t data) {
	if(addr % 4 != 0) {
		perror("");
		exit(1);
	}
	uint8_t byteZero   = (data & 0x000000FF);
	uint8_t byteOne    = (data & 0x0000FF00) >> 0x08;
	uint8_t byteTwo    = (data & 0x00FF0000) >> 0x10;
	uint8_t byteThree  = (data & 0xFF000000) >> 0x18;
	
	writeByte(addr, byteZero);
	writeByte(addr + 0x1, byteOne);
	writeByte(addr + 0x2, byteTwo);
	writeByte(addr + 0x3, byteThree);
}

uint8_t readByte(ramAddress addr) {
	uint32_t row = (uint32_t) addr / ramCols;
	uint32_t col = addr % ramCols;

	return ramMatrix[row][col];
}

uint32_t readWord(ramAddress addr){
	uint32_t byteZero  = readByte(addr);
	uint32_t byteOne   = readByte(addr + 1);
	uint32_t byteTwo   = readByte(addr + 2);
	uint32_t byteThree = readByte(addr + 3);
	return concatenate(byteThree, concatenate(byteTwo,concatenate(byteOne, byteZero)));
}
/*
* x and y must me in hex format
*/
uint32_t concatenate(uint32_t x, uint32_t y) {
    uint32_t pow = 0x10;
    while(y >= pow)
        pow *= 0x10;
    return (x * pow) + y;        
}

int main(int argc, char const *argv[])
{
	writeWord(0x20, 0x12345678);
	printf("%0x\n",readWord(0x20));
	return 0;
}