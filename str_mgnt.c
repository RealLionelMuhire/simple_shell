#include "shell.h"

/**
 * *_strchr - search c in string s
 * @s: string contains c
 * @c: charcter to search
 * Return: Pointer storing c
 */

char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}

	if (c == '\0')
	{
		return (s);
	}
	return (NULL);
}

/**
 * _strlen - returns the lenghth of o string
 * @s: string to return
 * Return: i at the end
 */

int _strlen(char *s)
{
	int i = 0;

	while (*s != '\0')
	{
		i++;
		s++;

	}
	return (i);

}


/**
 * _strcmp - compares 2 strings
 * @s1: string 1
 * @s2: string 2
 * Return: k always at success
 */

int _strcmp(char *s1, char *s2)
{
	int j = 0;

	if (s1 == NULL && s2 == NULL)
		return (0);

	else if (s1 == NULL)
		return (-1);

	else if (s2 == NULL)
		return (1);

	while (s1[j] != '\0' && s1[j] == s2[j])
	{
		j++;
	}
	return (s1[j] - s2[j]);
}

/**
 * *_strdup - copy a string and return a duplicate
 * @str: string to be copied
 * Return: duplicate otherwise NULL
 */
char *_strdup(char *str)
{
	char *n_str;

	if (str == NULL)
	{
		return (NULL);
	}

	n_str = (char *)malloc(strlen(str) + 1);

	if (n_str == NULL)
	{
		return (NULL);
	}

	strcpy(n_str, str);

	return (n_str);
}

/**
 * *_strcat - concatenate s trings
 * @dest: to be concatenated with src
 * @src: to transferred to dest
 * Return: dest at success
 */

char *_strcat(char *dest, char *src)
{
	int i = 0;
	int k;

	for (; dest[i] != '\0'; i++)
	{
		dest[i] = dest[i];
	}

	for (k = 0; src[k] != '\0'; k++)
	{
		dest[i + k] = src[k];
	}
	dest[i + k] = '\0';

	return (dest);
}
