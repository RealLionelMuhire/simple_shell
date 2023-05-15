#include "shell.h"
/**
 * _sprintf - Custom implementation of sprintf
 * @str: Buffer to store the formatted string
 * @format: Format string
 * Return: Number of characters written to the
 * --------buffer (excluding null terminator)
 */
int _sprintf(char *str, const char *format, ...)
{
	char *s;
	va_list args;
	int j = 0, n, len;

	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++; /* skip '%' */
			switch (*format)
			{
				case 's':
					s = va_arg(args, char *);
					len = 0;
					while (s[len] != '\0')
						len++;
					j += write_str(str + j, s, len);
				break;
				case 'd':
					n = va_arg(args, int);
					j += write_int(str + j, n);
				break;
				default:
				str[j++] = *format;
				break;
			}
		}
		else
		{
			str[j++] = *format;
		}
		format++;
		}
		va_end(args);
		str[j] = '\0'; /* null-terminate the string */
		return (j);
}

/**
 * check_env - checks if the typed variable is the environment var
 *
 * @h: head point in invironment list
 * @str: is the string passed
 * @data: shell data struct
 */

void check_env(l_v **h, char *str, sh_dt *data)
{
	char *env_name;
	int len, i;

	env_name = _strtok(str + 1, " \t\n;");
	if (!env_name)
		return;

	len = _strlen(env_name);
	for (i = 0; data->env[i]; i++)
	{
		if (_strncmp(data->env[i], env_name, len) == 0 &&
				data->env[i][len] == '=')
		{
			add_lv_n(h, len, data->env[i] + len + 1,
					_strlen(data->env[i] + len + 1));

			return;
		}
	}
	add_lv_n(h, len, NULL, 0);
}

/**
 * dollar_sign_h - check for $$ or $?
 *
 * @h: head of linked list
 * @str: is the input string
 * @stat: shell status
 * @data: shell data struct
 * Return: the number of chars checked in str
 * -------- and allows the user to continue processing the rest
 */

int dollar_sign_h(l_v **h, char *str, char stat, sh_dt data)
{
	int i, j, k;

	j = _strlen(str);
	k = _strlen(data->pid);

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?' || str[i + 1] == '$')
			{
				add_lv_n(h, 2, str[i + 1] == '?' ? stat : data->pid,
						str[i + 1] == '?' ? j : k);
				i++;
			}
			else if (str[i + 1] && str[i + 1] != '\n' && str[i + 1]
					!= '\0' && str[i + 1] != ' ' && str[i + 1] != '\t' && str[i + 1] != ';')
			{
				check_env(h, str + i, data);
				i++;
			}
			else
			{
				add_lv_n(h, 0, NULL, 0);
			}
		}
	}
	return (i);
}

/**
 * str_replace - it takes str and replaced them with variables
 * @head: head of ll
 * @s: input str
 * @n_s:new string
 * @n_l: new length
 *
 * Return: replaced str
 */
char *str_replace(l_v **head, char *s, char *n_s, n_l)
{
	l_v current = *head;
	int i, j, k;

	for (i = j = 0; i < n_l; i++, j++)
	{
		if (s[j] == '$')
		{
			if (current && current->val_len > 0)
			{
				for (k = 0; k < current->val_len; k++)
				{
					n_s[i] = current->var_val[k];
					i++;
				}
				j += current->var_len - 1;
				current = current->next;
			}
			else
			{
				n_s[i] = s[j];
			}
		}
		else
		{
			n_s[i] = s[j];
		}
	}
	return (n_s);
}

/**
 * replace_v - replace variables in the input string with
 * their corresponding values
 * @str: input string to be replaced
 * @data: struct containing all shell data
 *
 * Return: the string that was replaced
 */
char *replace_v(char *str, sh_dt *data)
{
	l_v *head = NULL, *idx;
	char *state = _itoa(data->status), *n_str;
	int new_len = 0;

	dollar_sign_h(&head, str, state, data);

	if (!head)
	{
		free(state);
		return (str);
	}

	idx = head;

	while (idx)
	{
		new_len += idx->val_len - idx->var_len;
		idx = idx->next;
	}

	new_len += _strlen(str);

	n_str = malloc(new_len + 1);
	n_str[new_len] = '\0';

	str_replace(head, str, n_str, new_len);

	free(str);
	free(state);
	free_lv(&head);

	return (n_str);
}
