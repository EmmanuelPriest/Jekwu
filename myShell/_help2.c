#include "shell.h"

/**
* aux_help - Help information for the inbuilt help.
*
* Return: nothing
*/
void aux_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tShows inbuilt commands information.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Shows inbuilt commands brief summaries.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
* aux_help_alias - Help information for the inbuilt alias.
*
* Return: nothing
*/
void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or show aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
* aux_help_cd - Help information for the inbuilt alias.
*
* Return: nothing
*/
void aux_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
