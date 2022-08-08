#include "shell.h"

/**
* _strdup - function that duplicates a string in the heap memory
* @s: char pointer string
*
* Return: the duplicated string
*/
char *_strdup(const char *s)
{
	char *new;
	size_t length;

	length = _strlen(s);
	new = malloc(sizeof(char) * (length + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, length + 1);
	return (new);
}

/**
* _strlen - function that returns the length of a string
* @s: character pointer
*
* Return: the string length
*/
int _strlen(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
* cmp_chars - function that compares char of strings
* @str: the input string
* @delim: the delimiter
*
* Return: 1 if strings are equal, 0 if not
*/
int cmp_chars(char str[], const char *delim)
{
	unsigned int n, m, x;

	for (n = 0, x = 0; str[n]; n++)
	{
		for (m = 0; delim[m]; m++)
		{
			if (str[n] == delim[m])
			{
				x++;
				break;
			}
		}
	}
	if (n == x)
		return (1);
	return (0);
}

/**
* _strtok - function that splits a string using delimiters
* @str: the input string
* @delim: the delimiter
*
* Return: the splited string
*/
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int n, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		n = _strlen(str);
		str_end = &str[n]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (n = 0; delim[n]; n++)
		{
			if (*splitted == delim[n])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}

/**
* _isdigit - function that defines if string passed is a number
* @s: the input string
*
* Return: 1 if string is a number, 0 if otherwise
*/
int _isdigit(const char *s)
{
	unsigned int n;

	for (n = 0; s[n]; n++)
	{
		if (s[n] < 48 || s[n] > 57)
			return (0);
	}
	return (1);
}
