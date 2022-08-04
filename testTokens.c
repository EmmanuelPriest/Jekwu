#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * tokens - splits a string and returns an array of each 
 * word of the string
 * @text - pointer to string
 *
 * Return:  array of strings
 */

char **tokens(char *text)
{

	char **words;
	const char *delim = " ";
	int i;
	int count_delim = 1;
	
	i = 0;
	while (text[i])
	{
		if (text[i] == delim[0])
			count_delim++;
		i++;
	}

	words = malloc(sizeof(char *) * count_delim);

	words[0] = strtok(text, delim);
	
	for (i = 1; i < count_delim; i++)
	{
		words[i] = strtok(NULL, delim);
	}
	free(words);

	return (words);
}

int main(void)
{
	char text[] = "something is here";
	char *words;
	char *delim = " ";

	words = strtok(text, delim);

	while (words)
	{
		printf("arguments: %s\n", words);
		words = strtok(NULL, delim);
	}

	return (0);
}
