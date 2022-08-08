#include "shell.h"

/**
* cmp_env_name - func that compares env variables names with the name passed
* @nenv: name of the environment variable
* @name: name passed
*
* Return: 0 if they are not equal, another value if they are
*/
int cmp_env_name(const char *nenv, const char *name)
{
	int n;

	for (n = 0; nenv[n] != '='; n++)
	{
		if (nenv[n] != name[n])
		{
			return (0);
		}
	}

	return (n + 1);
}

/**
* _getenv - function that gets an environment variable
* @name: the name of the environment variable
* @_environ: the environment variable
*
* Return: value of the environment variable if it is found
* otherwise NULL
*/
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int n, move;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	move = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (n = 0; _environ[n]; n++)
	{
		/* If name and env are equal */
		move = cmp_env_name(_environ[n], name);
		if (move)
		{
			ptr_env = _environ[n];
			break;
		}
	}

	return (ptr_env + move);
}

/**
* _env - function that prints the evironment variables
* @datash: relevant data
*
* Return: 1 on success
*/
int _env(data_shell *datash)
{
	int n, m;

	for (n = 0; datash->_environ[n]; n++)
	{

		for (m = 0; datash->_environ[n][m]; m++)
			;

		write(STDOUT_FILENO, datash->_environ[n], m);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->stat = 0;

	return (1);
}
