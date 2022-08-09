#include "shell.h"

/**
* readLine - function that reads the input string
* @i_eof: getline function return value
*
* Return: the input string
*/
char *readLine(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
