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

			i++
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


