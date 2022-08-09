#include "shell.h"

/**
* check_env - function that checks if the typed variable is an env variable
* @head: head of linked list
* @input: the input string
* @data: data structure
*
* Return: nothing
*/
void check_env(r_var **head, char *input, data_shell *data)
{
	int row, chr, m, lengthVal;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (m = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lengthVal = _strlen(_envr[row] + chr + 1);
				add_rvar_node(head, m, _envr[row]
						+ chr + 1, lengthVal);
				return;
			}

			if (input[m] == _envr[row][chr])
				m++;
			else
				break;
		}
	}

	for (m = 0; input[m]; m++)
	{
		if (input[m] == ' ' || input[m] == '\t' || input[m] == ';'
				|| input[m] == '\n')
			break;
	}

	add_rvar_node(head, m, NULL, 0);
}

/**
* checkVars - function that checks if the typed variable is $$ or $?
* @head: the linked list head
* @input: the input string
* @st: last status of the Shell
* @data: data structure
*
* Return: nothing
*/
int checkVars(r_var **head, char *input, char *st, data_shell *data)
{
	int n, last, lastpd;

	last = _strlen(st);
	lastpd = _strlen(data->pid);

	for (n = 0; input[n]; n++)
	{
		if (input[n] == '$')
		{
			if (input[n + 1] == '?')
				add_rvar_node(head, 2, st, last), n++;
			else if (input[n + 1] == '$')
				add_rvar_node(head, 2, data->pid, lastpd), n++;
			else if (input[n + 1] == '\n')
				add_rvar_node(head, 0, NULL, 0);
			else if (input[n + 1] == '\0')
				add_rvar_node(head, 0, NULL, 0);
			else if (input[n + 1] == ' ')
				add_rvar_node(head, 0, NULL, 0);
			else if (input[n + 1] == '\t')
				add_rvar_node(head, 0, NULL, 0);
			else if (input[n + 1] == ';')
				add_rvar_node(head, 0, NULL, 0);
			else
				check_env(head, input + n, data);
		}
	}

	return (n);
}

/**
* replacedInput - function that replaces string into variables
* @head: the linked list head
* @input: the input string
* @new_input: new input string (replaced)
* @newLength: the new length
*
* Return: replaced string
*/
char *replacedInput(r_var **head, char *input, char *new_input, int newLength)
{
	r_var *index;
	int n, m, x;

	index = *head;
	for (m = n = 0; n < newLength; n++)
	{
		if (input[m] == '$')
		{
			if (!(index->length_var) && !(index->length_val))
			{
				new_input[n] = input[m];
				m++;
			}
			else if (index->length_var && !(index->length_val))
			{
				for (x = 0; x < index->length_var; x++)
					m++;
				n--;
			}
			else
			{
				for (x = 0; x < index->length_val; x++)
				{
					new_input[n] = index->value[x];
					n++;
				}
				m = m + (index->length_var);
				n--;
			}
			index = index->next;
		}
		else
		{
			new_input[n] = input[m];
			m++;
		}
	}

	return (new_input);
}

/**
* repVar - calls functions to replace string into vars
* @input: the input string
* @datash: data structure
*
* Return: replaced string
*/
char *repVar(char *input, data_shell *datash)
{
	r_var *head, *index;
	char *status, *new_input;
	int oldLength, newLength;

	status = aux_itoa(datash->stat);
	head = NULL;

	oldLength = checkVars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	newLength = 0;

	while (index != NULL)
	{
		newLength += (index->length_val - index->length_var);
		index = index->next;
	}

	newLength = newLength + oldLength;

	new_input = malloc(sizeof(char) * (newLength + 1));
	new_input[newLength] = '\0';

	new_input = replacedInput(&head, input, new_input, newLength);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
