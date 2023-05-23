#include "shell.h"

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
