#include "shell.h"

/**
* getError - function that calls the error according to the inbuilt,
* syntax or permission
* @datash: data structure that contains arguments
* @eval: the error value
*
* Return: error
*/
int getError(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(datash);
		break;
	case 126:
		error = error_path_126(datash);
		break;
	case 127:
		error = errorNotFound(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = errorExitShell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->stat = eval;
	return (eval);
}
