#include "shell.h"

/**
* getInbuilt - inbuilt function that parses the command in the arg
* @cmd: the command
*
* Return: function pointer of the inbuilt command
*/
int (*getInbuilt(char *cmd))(data_shell *)
{
	inbuilt_t inbuilt[] = {
		{ "env", _env },
		{ "exit", exitShell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", getHelp },
		{ NULL, NULL }
	};
	int n;

	for (n = 0; inbuilt[n].name; n++)
	{
		if (_strcmp(inbuilt[n].name, cmd) == 0)
			break;
	}

	return (inbuilt[n].f);
}
