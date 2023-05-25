#include "shell.h"
/**
 * sigHandler - handle Ctrl+C to prompt the user
 * @sigNum: signal Handler
 */

void sigHandler(int sigNum)
{
	if (sigNum == SIGINT)
		PRINT("\n$ ");
}

/**
 * data_init - initializes all data
 * @av: argument vector
 * @data: struct containing data
 */

void data_init(char **av, sh_dt *data)
{
	unsigned int i;

	_memset(data, 0, sizeof(sh_dt));
	data->av = av;
	data->count = 1;

	for (i = 0; environ[i]; i++)
		;
	data->env = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data->env[i] = _strdup(environ[i]);
		if (!data->env[i])
		{
			free_d(&data);
			return;
		}
	}

	data->env[i] = NULL;
	data->pid = _itoa(getpid());
}


/**
 * hash_hand - handles hash comments
 * @str: string passed
 * Return: The whole input when the comment is removed
 */

char *hash_hand(char *str)
{
	int i = 0, j = 0;

	while (str[i])
	{
		if (str[i] == '#' && (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t' || str[i - 1] == ';'))
		{
			str[i] = '\0';
			break;
		}
		i++;
	}

	if (j)
		str = _realloc(str, i, j + 1);
	return str;
}

/**
 * get_input - get all input from the user
 * @ret: and integer to return, from the getline fun
 * Return: the users command entry
 */

char *get_input(int *ret)
{
	char *cmd = NULL;
	size_t n = 0;

	*ret = getline(&cmd, &n, stdin);

	return (cmd);
}
