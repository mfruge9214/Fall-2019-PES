#include <stdio.h>


#define LEFT 	0
#define RIGHT 	1

void testLast4Bits(int value);
int ReverseByteOrder(int value);
unsigned short rotateBits(int value, int num_bits, int direction);



int main(int argc, char const *argv[])
{
	int Data = 0xCAFE;
	int nextData = 0x0000;
	// int tempData = 0x0000;
	printf("Starting integer value: 0x%04X\r\n", Data);

	/* Test if 3 of the last 4 bits are on, and return the value of the last 4 bits*/
	testLast4Bits(Data);
	// printf("Reverse byte order\n");
	nextData = ReverseByteOrder(Data);
	printf("%X\n", nextData);
	testLast4Bits(nextData);
	nextData = rotateBits(nextData, 4, LEFT);
	printf("%X\n", nextData);
	nextData = rotateBits(nextData, 4, RIGHT);
	printf("%X\n", nextData);
	return 0;
}


void testLast4Bits(int value)
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
	printf("0X%04X\r\n", result);
}

int ReverseByteOrder(int value)
{

	// printf("Reversing Data: 0x%04X\r\n", value);
	int ModData = 0x0000;
	int extraction = 0x00FF;
	int shift = 8;
	int extractedValue = 0x00;

	extractedValue = value & extraction;
	// printf("Extracted value: 0x%02X\r\n", extractedValue);

	ModData = extractedValue;

	ModData = ModData << shift;
	extraction = 0xFF00;
	// printf("Mod Data after shift: 0x%04X\r\n", ModData);

	extractedValue = value & extraction;
	

	extractedValue = extractedValue >> shift;
	// printf("Extracted value: 0x%02X\r\n", extractedValue);

	ModData = ModData | extractedValue;

	return ModData;	
}


unsigned short rotateBits(int value, int num_bits, int direction)		/* https://www.geeksforgeeks.org/rotate-bits-of-an-integer/ */
{

	if(direction == LEFT)	// Left
	{
		return (unsigned short) ((value << num_bits) | (value >> (16 - num_bits)));
	}

	else if (direction == RIGHT)	// Right
	{
		return (unsigned short) ((value >> num_bits) | (value) << (16 - num_bits));
	}

	else return -1;
}