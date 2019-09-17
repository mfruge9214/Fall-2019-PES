/*
File: Program3.c
Description: This source file implements Program 3 of ESE Project 1
Author: Mike Fruge & Mark Hinkle
Tools: GCC99 library & GNU toolchain
Sources: https://www.geeksforgeeks.org/rotate-bits-of-an-integer/
*/



#include <stdio.h>
#include <stdint.h>


#define LEFT 	(0)
#define RIGHT 	(1)


void testLast4Bits(uint16_t value);
int ReverseByteOrder(uint16_t value);
unsigned short rotateBits(uint16_t value, uint16_t num_bits, uint16_t direction);
void printBinary(uint16_t value);


int main(int argc, char const *argv[])
{
	uint16_t Data = 0xCAFE;
	uint16_t nextData = 0x0000;
	printf("0x%04X\r\n", Data);

	/* Test if 3 of the last 4 bits are on, and return the value of the last 4 bits*/
	testLast4Bits(Data);
	// printf("Reverse byte order\n");
	nextData = ReverseByteOrder(Data);
	printf("0X %X\n", nextData);
	testLast4Bits(nextData);
	nextData = rotateBits(nextData, 4, LEFT);
	printf("0X %X\n", nextData);
	testLast4Bits(nextData);
	nextData = rotateBits(nextData, 4, RIGHT);
	printf("0X %X\n", nextData);
	testLast4Bits(nextData);
	return 0;
}


void testLast4Bits(uint16_t value)
{
	int compare = 0xF;
	int result = (compare) & (value);

	if(result == 7 || result == 11 || result >= 13)
	{
		printf("true\r\n");
	}
	else
	{
		printf("false\r\n");
	}
	printBinary(result);
}

void printBinary(uint16_t value)
{
	printf("0b'");

	if(value >= 8)
	{
		printf("1");
		value = value - 8;
	}
	else
	{
		printf("0");
	}

	if(value >= 4)
	{
		printf("1");
		value = value - 4;
	}
	else
	{
		printf("0");
	}

	if(value >= 2)
	{
		printf("1");
		value = value - 2;
	}
	else
	{
		printf("0");
	}

	if(value >= 1)
	{
		printf("1");
		value = value - 1;
	}
	else
	{
		printf("0");
	}

	printf("\r\n");
}

int ReverseByteOrder(uint16_t value)
{
	int ModData = 0x0000;
	int extraction = 0x00FF;
	int shift = 8;
	int extractedValue = 0x00;

	extractedValue = value & extraction;

	ModData = extractedValue;

	ModData = ModData << shift;
	extraction = 0xFF00;

	extractedValue = value & extraction;
	

	extractedValue = extractedValue >> shift;

	ModData = ModData | extractedValue;

	return ModData;	
}


uint16_t rotateBits(uint16_t value, uint16_t num_bits, uint16_t direction)		/* https://www.geeksforgeeks.org/rotate-bits-of-an-integer/ */
{

	if(direction == LEFT)	// Left
	{
		return (value << num_bits) | (value >> (16 - num_bits));
	}

	else if (direction == RIGHT)	// Right
	{
		return (value >> num_bits) | (value) << (16 - num_bits);
	}

	else return -1;
}