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
		*n += 1;

	if (p[*n])
		*n += 1;

	return (0);
}


/**
 * loc_exec - locates a command
 * @cmd: command name
 * @env: environment variables
 *
 * Return: location of the command.
 */
char *loc_exec(char *cmd, char **env)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = get_env("PATH", env);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cur_dir(path, &i))
			{
				if (stat(cmd, &st) == 0)
					return (_strdup(cmd));
			}
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_sprintf(dir, "%s/%s", token_path, cmd);

			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));

		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));
	return (NULL);
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
		acc_res = access(ch, X_OK);
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

/**
 * error_env - error message for env in get_env.
 * @data: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(sh_dt *data)
{
	char *counter_str = _itoa(data->count);
	char *msg = ": Unable to add/remove from environment\n";
	int total_length = _strlen(data->av[0]) + _strlen(counter_str) +
					   _strlen(data->args[0]) + _strlen(msg) + 4;

	char *error_msg = malloc(sizeof(char) * (total_length + 1));

	if (error_msg == NULL)
	{
		free(counter_str);
		return (NULL);
	}

	_sprintf(error_msg, "%s: %s: %s%s", data->av[0],
			counter_str, data->args[0], msg);
	free(counter_str);

	return (error_msg);
}

/**
 * err_p_126 - error message for path and failure denied permission.
 * @data: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *err_p_126(sh_dt *data)
{
	char *counter_str = _itoa(data->count);
	char *error_msg = malloc(sizeof(char) * (_strlen(data->av[0]) +
				_strlen(counter_str) + _strlen(data->args[0]) + 24 + 1));
	if (error_msg == NULL)
	{
		free(error_msg);
		free(counter_str);
		return (NULL);
	}

	_sprintf(error_msg, "%s: %s: %s: Permission denied\n",
			data->av[0], counter_str, data->args[0]);
	free(counter_str);

	return (error_msg);
}
