#include "shell.h"

/**
* withoutComment - function that deletes comments from the input
* @input: the input string
*
* Return: input without comments
*/
char *withoutComment(char *input)
{
	int n, up_to = 0;

	for (n = 0; input[n]; n++)
	{
		if (input[n] == '#')
		{
			if (n == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[n - 1] == ' ' || input[n - 1] == '\t'
					|| input[n - 1] == ';')
				up_to = n;
		}
	}

	if (up_to != 0)
	{
		input = _realloc(input, n, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

/**
* shellLoop - function that acts as the loop of shell
* @datash: relevant data (av, input, args)
*
* Return: nothing
*/
void shellLoop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = readLine(&i_eof);
		if (i_eof != -1)
		{
			input = withoutComment(input);
			if (input == NULL)
				continue;

			if (checkSyntaxError(datash, input) == 1)
			{
				datash->stat = 2;
				free(input);
				continue;
			}
			input = repVar(input, datash);
			loop = splitCmd(datash, input);
			datash->count += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
