#include "shell.h"

/**
 * add_lv_n - it adds the a variable node at linked list of variables
 * @head: is head node
 * @lvr: variable length
 * @v: value of that variable
 * @lvl: value length
 *
 * Return: the address of head node
 */

l_v *add_lv_n(lv **head, int lvr, int *v, int lvl)
{
	l_v *tmp;
	l_v *new = malloc(sizeof(l_v));
	if(!new)
		return (NULL);

	new->var_len = lvr;
	new->var_val = v;
	new->val_len = lvl;
	new->next = NULL;

	if (!(*head))
		*head = new;
	else
	{
		*tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

