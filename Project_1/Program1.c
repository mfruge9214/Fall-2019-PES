/*
File: Program1.c
Description: This source file implements Program 1 of ESE Project 1
Author: Mike Fruge & Mark Hinkle
Tools: GCC99 library & GNU toolchain
*/

#include <stdio.h>
#include <stdint.h>

#define OCT_SZ      8
#define DEC_SZ      10
#define HEX_SZ		16

#define NIBBLE_SZ   4
#define BYTE_SZ     8
#define BYTE2_SZ    16

#define MAX_UINT4   15
#define MIN_INT4    -8
#define MAX_UINT8   255
#define MIN_INT8    -128
#define MAX_UINT16  65535
#define MIN_INT16   -32768

#define	no_error       0b0000
#define	invalid_radix  0b0001
#define	invalid_opsize 0b0010
#define	invalid_val    0b0100

struct input{
	uint32_t value;
	uint32_t radix;
	uint32_t Op_Size;
};

int oct_to_dec(int oct)
{
	int dec = 0;
	int base = 1;
	int digit;

	while(oct) {
		digit = oct % 10;
		oct = oct / 10;
		dec += (digit * base);
		base = base * 8;
	}
	
	return dec;
}

int question1(int val, int radix, int op_size)
{

	int DEC_VAL, ABS_VAL, temp, cnt;
	int BIN_VAL[op_size], SOC_VAL[op_size], STC_VAL[op_size], SAM_VAL[op_size];
	// int BIN_VAL[op_size] = {0}; 
	// int SOC_VAL[op_size] = {0};
	// int STC_VAL[op_size] = {0};
	// int SAM_VAL[op_size] = {0};

	int MAX, MIN = 0;


	/********** Check for errors **********/
	uint8_t err_flag = no_error;

	if((radix != OCT_SZ) && (radix != DEC_SZ) && (radix != HEX_SZ)) 
	{
		err_flag |= invalid_radix;
	}
	else 
	{
		/* Compute Decimal Value */
		if(radix == OCT_SZ) 
		{
			DEC_VAL = oct_to_dec(val);
		}
		else 
		{               
			DEC_VAL = val;
		}

		if(op_size == NIBBLE_SZ) 
		{
			if((DEC_VAL > MAX_UINT4) || (DEC_VAL < MIN_INT4)) 
			{
				err_flag |= invalid_val;
			}
			MAX = MAX_UINT4;
		}
		else if(op_size == BYTE_SZ) {
			if((DEC_VAL > MAX_UINT8) || (DEC_VAL < MIN_INT8)) 
			{
				err_flag |= invalid_val;
			}
			MAX = MAX_UINT8;
		}
		else if(op_size == BYTE2_SZ) {
			if((DEC_VAL > MAX_UINT16) || (DEC_VAL < MIN_INT16)) 
			{
				err_flag |= invalid_val;
			}
			MAX = MAX_UINT16;
		}
		else {
			err_flag |= invalid_opsize;
		}
	}

	if(err_flag) 
	{
		printf("Invalid Input(s) to function:\n");
		if(err_flag & invalid_radix) 
		{
			printf("  Invalid radix value (only expects input of 8, 10, or 16)\n");
		}
		if(err_flag & invalid_opsize) 
		{
			printf("  Invalid operand size (only expects input of 4, 8, or 16)\n");
		}
		if(err_flag & invalid_val)
		{
			printf("  Value is outside operand size bounds\n");
		}
		printf("\n\n");
		//exit function
		return err_flag;
	}


	/********** Compute Values ************/
	if(DEC_VAL < 0) ABS_VAL = -DEC_VAL;
	else            ABS_VAL = DEC_VAL;
	
	temp = ABS_VAL;
	cnt = 0;

	// Binary (abs)
	while(temp)
	{
		BIN_VAL[cnt] = temp % 2;
		temp = temp / 2;
		cnt++;
	}

	// Signed Binary Arrays
	if(DEC_VAL < 0)
	{
		// Fill arrays
		for(int i = 0; i < op_size; i++)
		{
			SAM_VAL[i] = BIN_VAL[i];       // Sign and Magnitude
			SOC_VAL[i] = !(BIN_VAL[i]);    // Signed Ones Compliment
			STC_VAL[i] = SOC_VAL[i];       // Signed Twos Compliment
		}

		// Make sure last bit of SAM can signify sign - if not show error
		if(SAM_VAL[op_size - 1] == 0)
		{
			SAM_VAL[op_size - 1] = 1;
		}
		else
		{
			SAM_VAL[0] = 2;     // error
		}

		// Make sure the SOC binary string is seen as negative - if not show error
		if(SOC_VAL[op_size - 1] != 1)
		{
			SOC_VAL[0] = 2;     // error
		}

		// Change STC_VAL from a ones compliment to a twos compliment
		cnt = 0;
		while(cnt < op_size)
		 {
			if(STC_VAL[cnt] == 1) 
			{
				STC_VAL[cnt] = 0;
				cnt++;
			}
			else
			{
				STC_VAL[cnt] = 1;
				break;
			}
		}

		// Make sure the STC binary string is seen as negative - if not show error
		if(SOC_VAL[op_size - 1] != 1)
		{
			STC_VAL[0] = 2;     // error
		}
	}
	else
	{
		if(BIN_VAL[op_size - 1] == 1) 
		{
			SAM_VAL[0] = 2;     // error
			SOC_VAL[0] = 2;     // error
			STC_VAL[0] = 2;     // error
		}
		else
		{
			for(int i = 0; i < op_size; i++)
			{
				SAM_VAL[i] = BIN_VAL[i];       // Sign and Magnitude
				SOC_VAL[i] = BIN_VAL[i];       // Signed Ones Compliment
				STC_VAL[i] = BIN_VAL[i];       // Signed Twos Compliment
			}
		}
	}
    
    
	/*********** Print Table **********/
	printf("Input:    Value %d,    radix %d,    operand size %d\n", val, radix, op_size);              //header1
	printf("Output:                      Value                  Maximum                  Minimum\n");  //header2


	//Binary (abs)
	printf("Binary (abs)                 0b");
	for(int i = (op_size - 1); i >= 0; i--) 
	{
		printf("%d", BIN_VAL[i]);
	}

	printf("                 0b");
	for(int i = 0; i < op_size; i++)
	{
		printf("1");
	}

	printf("                 0b");
	for(int i = 0; i < op_size; i++)
	{
		printf("0");
	}
	printf("\n");

	//Octal (abs)
	printf("Octal (abs)                  %o", ABS_VAL);
	printf("                       %o                    %o\n", MAX, MIN);

	//Decimal (abs)
	printf("Decimal (abs)                %d", ABS_VAL);
	printf("                       %d                    %d\n", MAX, MIN);

	//Hexadecimal (abs)
	printf("Hexadecimal (abs)            0x%x", ABS_VAL);
	printf("                       0x%x                    0x%x\n", MAX, MIN);

	//Signed One's Compliment
	printf("Signed One's Compliment      ");
	if(SOC_VAL[0] == 2) 
	{
		printf("Error     ");
	}
	else
	{
		printf("0b");
		for(int i = (op_size - 1); i >= 0; i--) 
		{
			printf("%d", SOC_VAL[i]);
		}
	}

	printf("                 0b0");
	for(int i = 1; i < op_size; i++)
	{
		printf("1");
	}

	printf("                 0b1");
	for(int i = 1; i < op_size; i++)
	{
		printf("0");
	}
	printf("\n");

	//Signed Two's Compliment
	printf("Signed Two's Compliment      ");
	if(STC_VAL[0] == 2) 
	{
		printf("Error     ");
	}
	else
	{
		printf("0b");
		for(int i = (op_size - 1); i >= 0; i--) 
		{
			printf("%d", STC_VAL[i]);
		}
	}

	printf("                 0b0");
	for(int i = 1; i < op_size; i++)
	{
		printf("1");
	}

	printf("                 0b1");
	for(int i = 1; i < op_size; i++)
	{
		printf("0");
	}
	printf("\n"); 

	//Sign-Magnitude
	printf("Sign-Magnitude               ");
	if(SAM_VAL[0] == 2) 
	{
		printf("Error     ");
	}
	else
	{
		printf("0b");
		for(int i = (op_size - 1); i >= 0; i--) 
		{
			printf("%d", SAM_VAL[i]);
		}
	}

	printf("                 0b0");
	for(int i = 1; i < op_size; i++)
	{
		printf("1");
	}

	printf("                 0b1");
	for(int i = 1; i < op_size; i++)
	{
		printf("1");
	}
	printf("\n"); 

	printf("\n\n");
	return err_flag;
}


int main(int argc, char const *argv[])
{

	struct input inputs[11];

	inputs[0].value = -6;
	inputs[0].radix = 10;
	inputs[0].Op_Size = 4;

	inputs[1].value = -6;
	inputs[1].radix = 9;
	inputs[1].Op_Size = 4;

	inputs[2].value = -6;
	inputs[2].radix = 10;
	inputs[2].Op_Size = 5;

	inputs[3].value = -9;
	inputs[3].radix = 10;
	inputs[3].Op_Size = 4;

	inputs[4].value = 237;
	inputs[4].radix = 10;
	inputs[4].Op_Size = 8;

	inputs[5].value = 0354;
	inputs[5].radix = 8;
	inputs[5].Op_Size = 8;

	inputs[6].value = 0xEB;
	inputs[6].radix = 16;
	inputs[6].Op_Size = 8;

	inputs[7].value = -125;
	inputs[7].radix = 10;
	inputs[7].Op_Size = 8;

	inputs[8].value = 65400;
	inputs[8].radix = 10;
	inputs[8].Op_Size = 8;


	inputs[9].value = 65400;
	inputs[9].radix = 10;
	inputs[9].Op_Size = 16;

	inputs[10].value = -32701;
	inputs[10].radix = 10;
	inputs[10].Op_Size = 16;

	int i=0;
    int ret[11];

	for(i=0; i<11; i++)
	{
        ret[i] = question1(inputs[i].value, inputs[i].radix, inputs[i].Op_Size);
	}
	
	return 0;
}
