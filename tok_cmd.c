#include "shell.h"

/**
 * ch_repl - it replaces &| for non-print chars
 * @str: passed input string
 * @bool: boolean
 *
 * Return: the replaced string
 */

char *ch_repl(char *str, int bool)
{
	int i = 0;

	if (bool == 0)
	{
		while (str[i])
		{
			if (str[i] == '|')
			{
				if (str[i + 1] != '|')
					str[i] = 16;
				else
					i++;
			}

			if (str[i] == '&')
			{
				if (str[i + 1] != '&')
					str[i] = 12;
				else
					i++;

			}

			i++;
		}
	}
	else
	{
		while (str[i])
		{
			str[i] = (str[i] == 16 ? '|' : str[i]);
			str[i] = (str[i] == 12 ? '&' : str[i]);
			i++;
		}
	}
	return (str);
}

/**
 * next_cmd - this helps to go to the next command
 * @s_ls: separators store linked list
 * @cmd: command store linked list
 * @data: shell data
 */

void next_cmd(l_sep **s_ls, cmd_st **cmd, sh_dt *data)
{
	l_sep *l = *s_ls;
	cmd_st *c = *cmd;
	int n = 1;

	while (l && n)
	{
		if (data->status == 0)
		{
			if (l->sep == '&' || l->sep == ';')
				n = 0;
			else if (l->sep == '|')
				c = c->next;
		}
		else
		{
			if (l->sep == '|' || l->sep == ';')
				n = 0;
			else if (l->sep == '&')
				c = c->next;
		}
		l = l->next;
	}

	*s_ls = l;
	*cmd = c;
}


/**
 * tok_line - tokenise the string inputted
 * @str: string to tokeninse
 * Return: tokens
 */

char **tok_line(char *str)
{
	size_t i = 0, size = TOK_SIZE;
	char **toks = malloc(sizeof(char *) * TOK_SIZE), *tok;

	if (!toks)
	{
		PRINT_ERR(": allocation error\n");
		exit(EXIT_FAILURE);
	}

	tok = _strtok(str, DELIMITER);

	while (tok)
	{
		toks[i++] = tok;

		if (i == size)
		{
			size += TOK_SIZE;
			toks = _dp_realloc(toks, i, sizeof(char *) * size);

			if (toks)
			{
				PRINT_ERR(": allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		tok = _strtok(NULL, DELIMITER);
	}
	return (toks);
}

/**
 * cmd_tok - tokenise commands
 * @data: struct containing shell data;
 * @str: input string
 *
 * Return: 0 or 1
 */

int cmd_tok(sh_dt *data, char *str)
{
	l_sep *h_s = NULL, *l_s;
	cmd_st *h_c = NULL, *l_c;
	int n;


	add_sep_cmd_n(&h_s, &h_c, str);
	

	l_s = h_s;
	l_c = h_c;

	while (l_c)
	{
		data->line = l_c->c_line;
		data->args = tok_line(data->line);
		n = blt_cmd_h(data);
		free(data->args);

		if (n == 0)
			break;

		next_cmd(&l_s, &l_c, data);

		if (l_c)
			l_c = l_c->next;
	}
	free_l_sep(&l_s);
	free_cmd_st(&l_c);

	return (n == 0 ? 0 : 1);
}
