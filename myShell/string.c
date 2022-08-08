#include "shell.h"

/**
* _strcat - function that concatenates two strings
* @dest: char pointer to the dest of the copied string
* @src: const char pointer to the source of string
*
* Return: dest
*/
char *_strcat(char *dest, const char *src)
{
	int n;
	int m;

	for (n = 0; dest[n] != '\0'; n++)
		;

	for (m = 0; src[m] != '\0'; m++)
	{
		dest[n] = src[m];
		n++;
	}

	dest[n] = '\0';
	return (dest);
}

/**
* *_strcpy - function that copies the string pointed to by src
* @dest: char pointer to the dest of the copied string
* @src: char pointer to the source of string
*
* Return: dest
*/
char *_strcpy(char *dest, char *src)
{
	size_t n;

	for (n = 0; src[n] != '\0'; n++)
	{
		dest[n] = src[n];
	}
	dest[n] = '\0';

	return (dest);
}

/**
* _strcmp - Function that compares two strings
* @s1: string to be compared
* @s2: string to be compared
*
* Return: Always 0
*/
int _strcmp(char *s1, char *s2)
{
	int n;

	for (n = 0; s1[n] == s2[n] && s1[n]; n++)
		;

	if (s1[n] > s2[n])
		return (1);
	if (s1[n] < s2[n])
		return (-1);
	return (0);
}

/**
* _strchr - function that locates a character in a string
* @s: a string
* @c: a char
*
* Return: the pointer to the first occurrence of the char c
*/
char *_strchr(char *s, char c)
{
	unsigned int n = 0;

	for (; *(s + n) != '\0'; n++)
		if (*(s + n) == c)
			return (s + n);
	if (*(s + n) == c)
		return (s + n);
	return ('\0');
}

/**
* _strspn - function that gets the length of a prefix substring
* @s: the initial segment
* @accept: accepted bytes
*
* Return: the number of accepted bytes
*/
int _strspn(char *s, char *accept)
{
	int n, m, bool;

	for (n = 0; *(s + n) != '\0'; n++)
	{
		bool = 1;
		for (m = 0; *(accept + m) != '\0'; m++)
		{
			if (*(s + n) == *(accept + m))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (n);
}
