#include "shell.h"

/**
 * count_repeats - counts the repeated number of chars
 * @s: passed string
 * @start: initial point to start counting
 * Return: the number of repeated chars in s
 */

int count_repeats(char *s, int start)
{
	int count = 0, i;
	char ch = s[start];

	if (!ch)
		return (0);
	for (i = start + 1; s[i]; i++)
	{
		if (ch == s[i])
		{
			count++;
		}
	}
	return (count);
}

/**
 * get_err_sep - finds the typo or syntax errors in separators
 * @str: input string
 * @i: index
 * @j: last character read
 *
 * Return: the error index, otherwise 0
 */

int get_err_sep(char *str, int i, char j)
{
	int count;

	if (!str)
		return (0);

	if (*str == ' ' || *str == '\t')
		return (get_err_sep(str + 1, i + 1, j));

	switch (*str)
	{
		case ';':
			if (j == '|' || j == '&' || j == ';')
				return (i);
			break;

		case '|':
			if (j == ';' || j == '&')
				return (i);
			if (j == '|')
			{
				count = count_repeats(str, 0);
				if (count == 0 || count > 1)
					return (i);
			}
			break;

		case '&':
			if (j == ';' || j == '|')
				return (i);
			if (j == '&')
			{
				count = count_repeats(str, 0);
				if (count == 0 || count > 1)
					return (i);
			}
			break;
		default:
			break;
	}
	return (get_err_sep(str + 1, i + 1, *str));
}

/**
 * synt_err_print - prints the syntax error
 * @data: struct containing shell data
 * @str: the input string
 * @i: index of the error
 * @bool: the bolean to control the message error
 */
void synt_err_print(sh_dt *data, char *str, int i, int bool)
{
	char *msg, *err, *count;
	const char *msg2 = ": Syntax error: \"", *msg3 = "\" unexpected\n";
	int len;

	switch (str[i])
	{
		case ';':
			msg = (bool == 0 ? (str[i + 1] == ';' ? ";;" : ";") :
					(str[i - 1] == '?' ? "::" : ";"));
			break;
		case '|':
			msg = (str[i + 1] == '|' ? "||" : "|");
			break;
		case '&':
			msg = (str[i + 1] == '&' ? "&&" : "&");
			break;
		default:
			msg = "";
			break;
	}

	count = _itoa(data->count);
	len = _sprintf(NULL, 0, "%s: %s%s%s%s", data->av[0],
			count, msg2, msg, msg3) + 1;
	err = malloc(sizeof(char) * len);
	if (!err)
	{
		free(count);
		return;
	}
	_sprintf(err, "%s: %s%s%s%s", data->av[0], count, msg2, msg, msg3);
	PRINT_ERR(err);
	free(err);
	free(count);
}

/**
 * idx_char - finds the index of the char
 * @str: string to finds the index
 * @idx: index
 * Return: 0 at success, -1 at failure
 */

int idx_char(char *str, int *idx)
{
	*idx = 0;

	while (str[*idx])
	{
		if (str[*idx] == ' ' || str[*idx] == '\t')
		{
			*idx += 1;
			continue;
		}

		if (str[*idx] == ';' || str[*idx] == '|' || str[*idx] == '&')
		{
			return (-1);
		}
		break;
	}
	return (0);
}

/**
 * err_synt_checker - helps to find and prints syntax errors
 * @data: struct containing shell data
 * @str: the input string to check
 *
 * Return: 1 if there is an error, 0 otherwise
 */
int err_synt_checker(sh_dt *data, char *str)
{
	int init = 0, f_ch, i;

	f_ch = idx_char(str, &init);
	if (f_ch < 0)
	{
		synt_err_print(data, str, init, 0);
		return (1);
	}

	i = get_err_sep(str + init, 0, *(str + init));

	if (i)
	{
		synt_err_print(data, str, init + 1, 1);
		return (1);
	}
	return (0);
}
