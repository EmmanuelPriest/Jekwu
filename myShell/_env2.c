#include "shell.h"

/**
* copyInfo - function that copies info to create a new env or alias
* @name: name (env or alias)
* @value: value (env or alias)
*
* Return: new env or alias
*/
char *copyInfo(char *name, char *value)
{
	char *new;
	int lengthName, lengthValue, length;

	lengthName = _strlen(name);
	lengthValue = _strlen(value);
	length = lengthName + lengthValue + 2;
	new = malloc(sizeof(char) * (length));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
* setEnv - function that sets an environment variable
* @name: name of the environment variable
* @value: value of the environment variable
* @datash: data structure (environ)
*
* Return: nothing
*/
void setEnv(char *name, char *value, data_shell *datash)
{
	int n;
	char *var_env, *name_env;

	for (n = 0; datash->_environ[n]; n++)
	{
		var_env = _strdup(datash->_environ[n]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[n]);
			datash->_environ[n] = copyInfo(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, n,
			sizeof(char *) * (n + 2));
	datash->_environ[n] = copyInfo(name, value);
	datash->_environ[n + 1] = NULL;
}

/**
* _setenv - function that compares env variable names with the name passed
* @datash: relevant data (env name and env value)
*
* Return: 1 on success
*/
int _setenv(data_shell *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		getError(datash, -1);
		return (1);
	}

	setEnv(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
* _unsetenv - function that deletes an environment variable
* @datash: relevant data (env name)
*
* Return: 1 on success
*/
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int n, m, x;

	if (datash->args[1] == NULL)
	{
		getError(datash, -1);
		return (1);
	}
	x = -1;
	for (n = 0; datash->_environ[n]; n++)
	{
		var_env = _strdup(datash->_environ[n]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			x = n;
		}
		free(var_env);
	}
	if (x == -1)
	{
		getError(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (n));
	for (n = m = 0; datash->_environ[n]; n++)
	{
		if (n != x)
		{
			realloc_environ[m] = datash->_environ[n];
			m++;
		}
	}
	realloc_environ[m] = NULL;
	free(datash->_environ[x]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
