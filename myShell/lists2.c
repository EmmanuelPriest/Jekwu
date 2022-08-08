#include "shell.h"

/**
* add_rvar_node - function that adds a variable at the end of a r_var list
* @head: the linked list head
* @lengthVar: the variable length
* @val: the variable value
* @lengthVal: the value length
*
* Return: address of the head
*/
r_var *add_rvar_node(r_var **head, int lengthVar, char *val, int lengthVal)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->length_var = lengthVar;
	new->value = val;
	new->length_val = lengthVal;

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
* free_rvar_list - function that frees a r_var list
* @head: the linked list head
*
* Return: nothing
*/
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *current;

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
