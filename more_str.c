#include "shell.h"

/**
 * _atoi - convert Ascii to Integer
 * @s: string to be converted into a number
 * Return: A conerted integer
 */

int _atoi(char *s)
{
	unsigned int res;
	int sign, i;

	sign = 1;
	res = 0;
	i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			res = res * 10 + (s[i] - '0');
		}
		else if (res > 0)
		{
			break;
		}
		i++;
	}
	return (sign * res);
}

/**
 * _strncmp - compare 2 string upto n bytes
 * @s1: 1st str to compare
 * @s2: 2nd str to compare
 * @n: the maximum number of bytes
 *
 * Return: the diference between 2 string.
 * ------- if s1 - s2 > 0, then +ve int
 * ------- if s1 - s2 < 0, then -ve int
 * ------- if s1 = s2, then 0
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n && s1 && s2; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);

	return (s1[i] - s2[i]);
}

/**
 * *_strcpy - copy a string pointed
 * @dest:destination
 * @src:source
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	char *ptr = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (ptr);
}
