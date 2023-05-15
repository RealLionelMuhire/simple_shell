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
 */

int dollar_sign(l_v **h, char *str, char stat, sh_dt data)
{
	int i, j, k;

	j = _strlen(str);
	k = _strlen(data->pid);

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				add_lv_n(h, 2, stat, j), i++;
		}
	}
}
