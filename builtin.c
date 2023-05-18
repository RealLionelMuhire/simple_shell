#include "shell.h"

/**
 * _builtin - finds the builtin command function pointer
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*_builtin(char *cmd))(sh_dt *data)
{
	blt_cmd builtins[] = {
		{ "env", handle_env },
		{ "exit", handle_exit },
		{ "setenv", handle_setenv },
		{ "unsetenv", handle_unsetenv },
		{ "cd", change_dir },
		{ NULL, NULL },
	};

	int i;

	for (i = 0; builtins[i].cmd != NULL; i++)
	{
		if  (_strcmp(builtins[i].cmd, cmd) == 0)
		{
			return (builtins[i].f);
		}
	}
	return (NULL);
}

/**
 * compare_var - compare environment variable names
 * @env_var: environment variables
 * @name: name
 *
 * Return: 0 for names taht are not equal, 1 when equal
 */
int compare_var(const char *env_var, const char *name)
{
	int i;

	for (i = 0; env_var[i] != '='; i++)
	{
		if (env_var[i] != name[i])
		{
			return (0);
		}
	}
	return (1);
}

/**
 * get_env - retrievesvalue of an environment variable
 * @name: name of environment variable
 * @env: environment variables
 *
 * Return: value of environment variable, otherwise NULL
 */
char *get_env(const *name, char **env)
{
	char *val;
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (compare_var(env[i], name))
		{
			val = env[i] + _strlen(name) + 1;
			return (val);
		}
	}
	return (NULL);
}

/**
 * handle_env - handles env command to print environment variables
 * @data: shell data
 *
 * Return: 1 on success
 */
int handle_env(sh_dt *data)
{
	int i;

	for (i = 0; data->env[i] != NULL; i++)
	{
		write(STDOUT_FILENO, data->env[i], _strlen(data->env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	data->status = 0;
	return (1);
}
