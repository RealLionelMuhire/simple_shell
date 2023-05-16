#include "shell.h"

/**
 * free_l_sep - free list of sep linked list
 * @h: head of linked list
 */

void free_l_sep(l_sep **h)
{
	l_sep *c = *h, *tmp;

	while (c)
	{
		tmp = c;
		c = c->next;
		free(tmp);
	}

	*h = NULL;
}

/**
 * free_cmd_st - free linked list of command store
 * @h: head of linked list
 */
void free_cmd_st(cmd_st **h)
{
	cmd_st *c = *h, *tmp;

	while (c)
	{
		tmp = c;
		c = c->next;
		free(tmp);
	}

	*h = NULL;
}
