#include "shell.h"

/**
* swapChar - function that swaps | and & for non-printed chars
* @input: the input string
* @bool: type of swap
*
* Return: swapped input string
*/
char *swapChar(char *input, int bool)
{
	int n;

	if (bool == 0)
	{
		for (n = 0; input[n]; n++)
		{
			if (input[n] == '|')
			{
				if (input[n + 1] != '|')
					input[n] = 16;
				else
					n++;
			}

			if (input[n] == '&')
			{
				if (input[n + 1] != '&')
					input[n] = 12;
				else
					n++;
			}
		}
	}
	else
	{
		for (n = 0; input[n]; n++)
		{
			input[n] = (input[n] == 16 ? '|' : input[n]);
			input[n] = (input[n] == 12 ? '&' : input[n]);
		}
	}
	return (input);
}

/**
* addNodes - function that adds separators and command lines in the lists
* @head_s: the separator list head
* @head_l: the command lines list head
* @input: the input string
*
* Return: nothing
*/
void addNodes(sep_list **head_s, line_list **head_l, char *input)
{
	int n;
	char *line;

	input = swapChar(input, 0);

	for (n = 0; input[n]; n++)
	{
		if (input[n] == ';')
			add_sep_node_end(head_s, input[n]);

		if (input[n] == '|' || input[n] == '&')
		{
			add_sep_node_end(head_s, input[n]);
			n++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swapChar(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
* goNext - function used to go to the next command line stored
* @list_s: the separator list
* @list_l: the command line list
* @datash: data structure
*
* Return: nothing
*/
void goNext(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->stat == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
* splitCmd - function that splits command lines according to
* the separators ;, | and &, and executes them
* @datash: data structure
* @input: the input string
*
* Return: 0 to exit, 1 to continue
*/
int splitCmd(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	addNodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = splitLine(datash->input);
		loop = executeLine(datash);
		free(datash->args);

		if (loop == 0)
			break;

		goNext(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
* splitLine - function that tokenizes the input string
* @input: the input string
*
* Return: the splitted string (tokens)
*/
char **splitLine(char *input)
{
	size_t bufsize;
	size_t n;
	char **tokens;
	char *token;

	bufsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bufsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (n = 1; token != NULL; n++)
	{
		if (n == bufsize)
		{
			bufsize = bufsize + TOK_BUFSIZE;
			tokens = _reallocdp(tokens, n, sizeof(char *) *
					bufsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n",
						18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[n] = token;
	}

	return (tokens);
}
