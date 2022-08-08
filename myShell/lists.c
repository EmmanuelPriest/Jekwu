#include "shell.h"

/**
* add_sep_node_end - function that adds a separator found @ the end of sep_list
* @head: the linked list head
* @sep: separator found (; | &)
*
* Return: address of the head
*/
sep_list *add_sep_node_end(sep_list **head, char separ)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->sep = separ;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
* free_sep_list - function that frees a sep_list
* @head: the linked list head
*
* Return: nothing
*/
void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
* add_line_node_end - function that adds a command line at the end of line_list
* @head: the linked list head
* @line: command line
*
* Return: address of the head
*/
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
* free_line_list - function that frees a line_list
* @head: the linked list head
*
* Return: nothing
*/
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}
