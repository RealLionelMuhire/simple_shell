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

l_v *add_lv_n(l_v **head, int lvr, char *v, int lvl)
{
	l_v *tmp;
	l_v *new = malloc(sizeof(l_v));

	if (!new)
		return (NULL);

	new->var_len = lvr;
	new->var_val = v;
	new->val_len = lvl;
	new->next = NULL;

	if (!(*head))
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * add_l_sep_n - adds a new node at thelist separators
 * @head: head the linked list
 * @s: separators
 * Return: a head a of new linked list
 */

l_sep *add_l_sep_n(l_sep **head, char s)
{
	l_sep *tmp;
	l_sep *new = malloc(sizeof(l_sep));

	if (!new)
		return (NULL);

	new->sep = s;
	new->next = NULL;

	if (*head == NULL)
		*head = new;

	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * add_cmd_st_n - adds a new node at the command store linked list
 * @h: head of the linked list
 * @cmd: commnand to add
 * Return: the head of the linked list
 */

cmd_st *add_cmd_st_n(cmd_st **h, char *cmd)
{
	cmd_st *tmp, *new;

	new = malloc(sizeof(cmd_st));

	if (!new)
		return (NULL);
	new->c_line = cmd;
	new->next = NULL;

	if (*h == NULL)
		*h = new;
	else
	{
		tmp = *h;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*h);
}

/**
 * add_sep_cmd_n - adds separators and commandline in their respective list
 * @h_s: head of separators list
 * @h_c: head of commands
 * @str: input sting passed
 */

void add_sep_cmd_n(l_sep **h_s, cmd_st **h_c, char *str)
{
	int i;
	char *tok;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '|' || str[i] == '&')
		{
			add_l_sep_n(h_s, str[i]);
			i++;
		}
		else if (str[i] == ';')
		{
			add_l_sep_n(h_s, str[i]);
		}
	}

	for (tok = _strtok(str, ";|&"); tok != NULL; tok = _strtok(NULL, ";|&"))
	{
		add_cmd_st_n(h_c, ch_repl(tok, 1));
	}
}
