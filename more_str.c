#include "shell.h"

/**
 * _strtok - tokenizes a string
 * @str: string to be tokenized
 * @delim: delimiter character
 *
 * Return: pointer to the next token
 */
char *_strtok(char *str, const char *delim)
{
	static char *last = NULL;
	char *token, *ptr;

	if(str == NULL && last == NULL)
		return(NULL);

	if (str != NULL)
		ptr = str;
	else
		ptr = lats;

	while (*ptr && _strchr(delim, *ptr))
		ptr++;
	if (*ptr == '\0')
		return(NULL);

	token = ptr;
	while (*ptr && _strchr(delim, *ptr))
		ptr++;
	if (*ptr == '\0')
		last = NULL;
	else
	{
		*ptr = '\0';
		last = ptr + 1;
	}
	return (token);
}
