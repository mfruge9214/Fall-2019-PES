#include <stdio.h>


int main(int argc, char const *argv[])
{
	// int i = 0;
	// int input_size;
	int code;
	char character;
	char* catagory;
	/*
	printf("How many inputs do you have?");
	scanf("%d", input_size);
	string buffer[input_size];
	*/

	printf("Please specify character code:\n");
	scanf("%d", &code);

	character = (char) code;

	if(code >= 'a' && code <= 'z')	catagory = "Lower Case";
	else if (code >= 'A' && code <= 'Z')	catagory = "Upper Case";
	else if (code >= '0' && code <= '9')	catagory = "Digit";
	else if (code <= ' ')	catagory = "Whitespace";
	else if (code >177)
	{
		printf("Not a valid character code\n");
		return -1;
	}
	else catagory = "Special Character";	


	printf("Code: %d 	Type:%s 	ASCII Char:%c", code, catagory, character);	
	return 0;
}