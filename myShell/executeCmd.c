#include "shell.h"

/**
* is_cdir - function that checks if ":" is in the current directory
* @path: char pointer
* @index: index pointer
*
* Return: 1 if the path is searchable in the cd, 0 if otherwise
*/
int is_cdir(char *path, int *index)
{
	if (path[*index] == ':')
		return (1);

	while (path[*index] != ':' && path[*index])
	{
		*index += 1;
	}

	if (path[*index])
		*index += 1;

	return (0);
}

/**
* _which - function that locates a command
* @cmd: command name
* @_environ: environment variable
*
* Return: location of the command
*/
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, n;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		n = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &n))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
* _executable - function that determines if it is an executable
* @datash: data structure
*
* Return: 0 if it is not an executable, other number if it is
*/
int _executable(data_shell *datash)
{
	struct stat st;
	int n;
	char *input;

	input = datash->args[0];
	for (n = 0; input[n]; n++)
	{
		if (input[n] == '.')
		{
			if (input[n + 1] == '.')
				return (0);
			if (input[n + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[n] == '/' && n != 0)
		{
			if (input[n + 1] == '.')
				continue;
			n++;
			break;
		}
		else
			break;
	}
	if (n == 0)
		return (0);

	if (stat(input + n, &st) == 0)
	{
		return (n);
	}
	getError(datash, 127);
	return (-1);
}

/**
* checkErrorCmd - function that verifies if user has permissions to access
* @dir: the destination directory
* @datash: data structure
*
* Return: 1 if there is an error, 0 if otherwise
*/
int checkErrorCmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		getError(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			getError(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			getError(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
* executeCmd - function that executes command lines
* @datash: relevant data (args and input)
*
* Return: 1 on success
*/
int executeCmd(data_shell *datash)
{
	pid_t pid;
	pid_t ppid;
	int state;
	int execute;
	char *dir;
	(void) ppid;

	execute = _executable(datash);
	if (execute == -1)
		return (1);
	if (execute == 0)
	{
		dir = _which(datash->args[0], datash->_environ);
		if (checkErrorCmd(dir, datash) == 1)
			return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execute == 0)
			dir = _which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + execute, datash->args, datash->_environ);
	}
	else if (pid < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			ppid = waitpid(pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->stat = state / 256;
	return (1);
}
