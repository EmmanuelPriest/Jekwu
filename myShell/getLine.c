#include "shell.h"

/**
* bringLine - function that assigns the line var for getLine
* @lineptr: Buffer that store the input str
* @buffer: str that is been called to line
* @n: size of line
* @m: size of buffer
*/
void bringLine(char **lineptr, size_t *n, char *buffer, size_t m)
{
	if (*lineptr == NULL)
	{
		if  (m > BUFSIZE)
			*n = m;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < m)
	{
		if (m > BUFSIZE)
			*n = m;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
* getLine - function that reads input from stream
* @lineptr: buffer that stores the input
* @n: size of buffer
* @stream: stream to be read from
*
* Return: number of bytes
*/
ssize_t getLine(char **lineptr, size_t *n, FILE *stream)
{
	int m;
	static ssize_t input;
	ssize_t ret;
	char *buffer;
	char a = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (a != '\n')
	{
		m = read(STDIN_FILENO, &a, 1);
		if (m == -1 || (m == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (m == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = a;
		input++;
	}
	buffer[input] = '\0';
	bringLine(lineptr, n, buffer, input);
	ret = input;
	if (m != 0)
		input = 0;
	return (ret);
}
