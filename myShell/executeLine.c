#include "shell.h"

/**
* executeLine - function that finds inbuilt commands
* @datash: relevant data (args)
*
* Return: 1 on success
*/
int executeLine(data_shell *datash)
{
	int (*inbuilt)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	inbuilt = getInbuilt(datash->args[0]);

	if (inbuilt != NULL)
		return (inbuilt(datash));

	return (executeCmd(datash));
}
