#include "shell.h"

/**
* rev_string - function that reverses a string
* @s: the input string
*
* Return: nothing
*/
void rev_string(char *s)
{
	int counter, n, m;
	char *str, temp;

	for (counter = 0; counter >= 0; counter++)
	{
		if (s[counter] == '\0')
			break;
	}
	str = s;

	for (n = 0; n < (counter - 1); n++)
	{
		for (m = n + 1; m > 0; m--)
		{
			temp = *(str + m);
			*(str + m) = *(str + (m - 1));
			*(str + (m - 1)) = temp;
		}
	}
}
