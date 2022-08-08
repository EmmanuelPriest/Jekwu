#include "shell.h"

/**
* getLength - function that gets the length of a number
* @n: integer number
*
* Return: Length of a number
*/
int getLength(int n)
{
	unsigned int m;
	int length = 1;

	if (n < 0)
	{
		length++;
		m = n * -1;
	}
	else
	{
		m = n;
	}
	while (m > 9)
	{
		length++;
		m = m / 10;
	}

	return (length);
}

/**
* aux_itoa - function that converts integer to string
* @n: integer number
*
* Return: a string
*/
char *aux_itoa(int n)
{
	unsigned int m;
	int length = getLength(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (n < 0)
	{
		m = n * -1;
		buffer[0] = '-';
	}
	else
	{
		m = n;
	}

	length--;
	do {
		*(buffer + length) = (m % 10) + '0';
		m = m / 10;
		length--;
	}
	while (m > 0)
		;
	return (buffer);
}

/**
* _atoi - function that converts a string to an integer
* @s: the input string
*
* Return: an integer
*/
int _atoi(char *s)
{
	unsigned int counter = 0, size = 0, oi = 0, z = 1, x = 1, y;

	while (*(s + counter) != '\0')
	{
		if (size > 0 && (*(s + counter) < '0' || *(s + counter) > '9'))
			break;

		if (*(s + counter) == '-')
			z = z * -1;

		if ((*(s + counter) >= '0') && (*(s + counter) <= '9'))
		{
			if (size > 0)
				x = x * 10;
			size++;
		}
		counter++;
	}

	y = counter - size;
	while (y < counter)
	{
		oi = oi + ((*(s + y) - 48) * x);
		x /= 10;
		y++;
	}
	return (oi * z);
}
