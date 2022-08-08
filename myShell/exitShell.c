#include "shell.h"

/**
* exitShell - function that exits the shell
* @datash: relevant data (stat and args)
*
* Return: 0 on success
*/
int exitShell(data_shell *datash)
{
	unsigned int uStat;
	int isDigit;
	int strLength;
	int bigNumber;

	if (datash->args[1] != NULL)
	{
		uStat = _atoi(datash->args[1]);
		isDigit = _isdigit(datash->args[1]);
		strLength = _strlen(datash->args[1]);
		bigNumber = uStat > (unsigned int)INT_MAX;
		if (!isDigit || strLength > 10 || bigNumber)
		{
			getError(datash, 2);
			datash->stat = 2;
			return (1);
		}
		datash->stat = (uStat % 256);
	}
	return (0);
}
