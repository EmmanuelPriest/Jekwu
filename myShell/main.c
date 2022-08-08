#include "shell.h"

/**
* freeData - function that frees data structure
* @datash: data structure
*
* Return: nothing
*/
void freeData(data_shell *datash)
{
	unsigned int n;

	n = 0;
	while (datash->_environ[n])
	{
		free(datash->_environ[n]);
		n++;
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
* setData - function that initializes data structure
* @datash: data structure
* @av: argument vector
*
* Return: nothing
*/
void setData(data_shell *datash, char **av)
{
	unsigned int n;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->stat = 0;
	datash->count = 1;

	for (n = 0; environ[n]; n++)
		;

	datash->_environ = malloc(sizeof(char *) * (n + 1));

	n = 0;
	while (environ[n])
	{
		datash->_environ[n] = _strdup(environ[n]);
		n++;
	}

	datash->_environ[n] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
* main - Entry point
* @ac: argument count
* @av: argument vector
*
* Return: 0 on success.
*/
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	setData(&datash, av);
	shellLoop(&datash);
	freeData(&datash);
	if (datash.stat < 0)
		return (255);
	return (datash.stat);
}
