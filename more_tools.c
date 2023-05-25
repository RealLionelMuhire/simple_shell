#include "shell.h"

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

	env_name = strtok(str + 1, " \t\n;");
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

int dollar_sign_h(l_v **h, char *str, char *stat, sh_dt *data)
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
 * str_replace - replace variables in the input string with
 * --------------their corresponding values
 * @head: head of the linked list
 * @input_str: input string to be replaced
 * @new_str: new string to store the replaced input
 * @new_len: length of the new string
 *
 * Return: the replaced input string
 */
char *str_replace(l_v **head, char *input_str, char *new_str, int new_len)
{
	l_v *current = *head;
	int i, j, k;

	for (i = j = 0; i < new_len; i++)
	{
		if (input_str[j] == '$')
		{
			if (current && current->val_len > 0)
			{
				for (k = 0; k < current->val_len; k++)
					new_str[i++] = current->var_val[k];
				j += current->var_len;
				i--;
			}
			else if (current && current->var_len > 0)
			{
				j += current->var_len;
				i--;
			}
			else
			{
				new_str[i] = input_str[j];
				j++;
			}
			current = current->next;
		}
		else
		{
			new_str[i] = input_str[j];
			j++;
		}
	}

	return (new_str);
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

	while (idx->next)
	{
		new_len += idx->val_len - idx->var_len;
		idx = idx->next;
	}

	new_len += _strlen(str) - (idx->var_len * 2);

	n_str = malloc(new_len + 1);
	n_str[new_len] = '\0';

	n_str = str_replace(&head, str, n_str, new_len);

	free(str);
	free(state);
	free_lv(&head);

	return (n_str);
}

/**
 * _isdigit - checks if c is a digit between '0' and '9'
 * @str: string to be checked
 * Return: 1 if c is a digit, 0 otherwise
 */
int _isdigit(char *str)
{
	int i;

	if (str == NULL || str[0] == '\0')
		return (0);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

