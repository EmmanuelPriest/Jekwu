#include "shell.h"

/**
* repeatedChar - function that counts the repetitions of a char
* @input: the input string
* @index: the index
*
* Return: index repetitions
*/
int repeatedChar(char *input, int index)
{
	if (*(input - 1) == *input)
		return (repeatedChar(input - 1, index + 1));

	return (index);
}

/**
* error_sep_op - function that finds syntax errors
* @input: the input string
* @index: the index
* @last: the last char read
*
* Return: index of error, 0 when there are no errors
*/
int error_sep_op(char *input, int index, char last)
{
	int counter;

	counter = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, index + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (index);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (index);

		if (last == '|')
		{
			counter = repeatedChar(input, 0);
			if (counter == 0 || counter > 1)
				return (index);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (index);

		if (last == '&')
		{
			counter = repeatedChar(input, 0);
			if (counter == 0 || counter > 1)
				return (index);
		}
	}

	return (error_sep_op(input + 1, index + 1, *input));
}

/**
* firstChar - function that finds index of the first char
* @input: the input string
* @n: the index
*
* Return: 1 if there is an error, 0 if otherwise
*/
int firstChar(char *input, int *n)
{
	for (*n = 0; input[*n]; *n += 1)
	{
		if (input[*n] == ' ' || input[*n] == '\t')
			continue;

		if (input[*n] == ';' || input[*n] == '|' || input[*n] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
* printSyntaxError - function that prints a syntax error when found
* @datash: the data structure
* @input: the input string
* @index: the index of the error
* @bool: for controling msg error
*
* Return: nothing
*/
void printSyntaxError(data_shell *datash, char *input, int index, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[index] == ';')
	{
		if (bool == 0)
			msg = (input[index + 1] == ';' ? ";;" : ";");
		else
			msg = (input[index - 1] == ';' ? ";;" : ";");
	}

	if (input[index] == '|')
		msg = (input[index + 1] == '|' ? "||" : "|");

	if (input[index] == '&')
		msg = (input[index + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datash->count);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length = length + _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
* checkSyntaxError - intermediate function to find and print a syntax error
* @datash: the data structure
* @input: the input string
*
* Return: 1 if there is an error, 0 if otherwise
*/
int checkSyntaxError(data_shell *datash, char *input)
{
	int begin = 0;
	int fChar = 0;
	int n = 0;

	fChar = firstChar(input, &begin);
	if (fChar == -1)
	{
		printSyntaxError(datash, input, begin, 0);
		return (1);
	}

	n = error_sep_op(input + begin, 0, *(input + begin));
	if (n != 0)
	{
		printSyntaxError(datash, input, begin + n, 1);
		return (1);
	}

	return (0);
}
