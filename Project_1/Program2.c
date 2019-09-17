#include <stdio.h>

#define NUM_INPUTS	20
int main(int argc, char const *argv[])
{
	char character;
	char* catagory;
	int i=0;
	char code[] = {66,114,117,99,101,32,83,97,121,115,32,72,105,33,7,9,50,48,49,57};

	for(i=0; i<NUM_INPUTS; i++)
	{
		character = code[i];

		if(character >= 'a' && character <= 'z')	catagory = "Lower Case";
		else if (character >= 'A' && character <= 'Z')	catagory = "Upper Case";
		else if (character >= '0' && character <= '9')	catagory = "Digit";
		else if (character <= ' ')	catagory = "Whitespace";
		else if (character >177)
		{
			printf("Not a valid character code\n");
			return -1;
		}
		else catagory = "Special Character";	


		printf("Code: %d 	Type:%s 	ASCII Char:%c \r\n", character, catagory, character);	
	}
	return 0;
}