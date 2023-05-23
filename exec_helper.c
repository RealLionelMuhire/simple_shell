#include "shell.h"

/**
 * is_cur_dir - checks is the char : is the current directory
 * @p: pointer character
 * @n: index
 * Return: 1 is the path p is searchable otherwise 0
 */
int is_cur_dir(char *p, int *n)
{
	if (p[*n] == ':')
		return (1);

	while (p[*n] && p[*n] != ':')
		(*i)++;

	if (p[*n])
		(*n)++;

	return (0);
}

/**
 * loc_exec - locate the executable commands
 * @cmd: command to locate
 * @env: environment variable
 * Return: command if is found otherwise NULL
 */
char loc_exec(char *cmd, char **env)
{
	char *path, *path_copy, *token, *dir;
	int dir_length, command_length;
	struct stat st;

	path = get_env("PATH", env);

	if (path)
	{
		path_copy = _strdup(path);
		command_length = _strlen(command);
		token = _strtok(path_copy, ":");
		while (token != NULL)
		{
			if (is_cur_dir(token, &(int)
						{0}) && stat(command, &st) == 0)
			{
				return (command);
			}
			dir_length = _strlen(token);
			dir = malloc(dir_length + command_length + 2);
			_sprintf(dir, "%s/%s", token, command);
			if (stat(dir, &st) == 0)
			{
				free(path_copy);
				return (dir);
			}
			free(dir);
			token = strtok(NULL, ":");
		}
		if (command[0] == '/' && stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
}

/**
 * err_checker - checks whether the user has permission on access
 * @ch: final destination dir
 * @data: structure containing shell data
 * Return: 1 if there is no permission or error, otherwise 0
 */

int err_checker(char *ch, sh_dt *data)
{
	int acc_res;

	if (ch == NULL)
	{
		get_err(data, 127);
		return (1);
	}

	if (_strcmp(data->args[0], ch) != 0)
		acc_res = access(dir, X_OK);
	else
		acc_res = access(data->args[0], X_OK);

	free(ch);

	if (acc_res == -1)
	{
		get_err(data, 126);
		return (1);
	}

	return (0);
}
