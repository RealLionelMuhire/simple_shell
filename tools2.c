#include "shell.h"


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

