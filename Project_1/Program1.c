#include <stdio.h>



struct input{
	int value;
	int radix;
	int Op_Size;
}

int main(int argc, char const *argv[])
{

	input inputs[11];

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
	
	return 0;
}