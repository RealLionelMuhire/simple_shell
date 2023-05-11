#include "shell.h"

/**
 * exit_shell - exits the shell.
 * @data: Pointer to the shell data struct
 * Return: Always return 0
 */
int exit_shell(sh_dt *data)
{
	int status = 0, n, i = 0;
	char *arg = data->args[1];

	if (data->args[1] != NULL)
	{
		i = 0;
		while (arg[i] != '\0')
		{
			n = _isdigit(arg[i]);
			if (!n)
			{
				printf("exit: Illegal number: %s\n", arg);
				break;

			}
			i++;
		}
		status = _atoi(arg);
	}
	free_d(data);
	fflush(stdout);
	exit(status);
}

/**
 * _intlen - Computes the number of digit in a number
 * @num: the number to computes
 *
 * Return: the length of the integer
 */
int _intlen(int num)
{
	int len = 0;

	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

/**
 * _itoa - converts an int into string array
 * @n: a number to convert into a string
 *
 * Return: a pointer to the converted null terminated string
 */
char *_itoa(unsigned int n)
{
	int len = 0, i = 0;
	char *s;

	len = _intlen(n);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	*s = '\0';
	while (n / 10)
	{
		s[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	s[i] = (n % 10) + '0';
	arr_rev(s, len);
	s[i + 1] = '\0';
	return (s);
}

/**
 * arr_rev - reverses array string
 * @arr: an array or string to reverse
 * @len: the array or string length
 */
void arr_rev(char *arr, int len)
{
	int i;
	char tmp;

	for (i = 0; i < (len / 2); i++)
	{
		tmp = arr[i];
		arr[i] = arr[(len - 1) - i];
		arr[(len - 1) - i] = tmp;
	}
}

