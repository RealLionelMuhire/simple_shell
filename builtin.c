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
		/*{ "unsetenv", handle_unsetenv },
		{ "cd", change_dir },*/
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
char *get_env(char *name, char **env)
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

/**
 * handle_exit - executes exit command to exit the shell
 * @data: shell data struct
 *
 * Return: always 0 on success
 */
int handle_exit(sh_dt *data)
{
	unsigned int exit_stt;
	int valid = 1, args_len = 0, is_large = 0;

	if (data->args[1] != NULL)
	{
		exit_stt = _atoi(data->args[1]);

		valid = _isdigit(data->args[1]);
		args_len = _strlen(data->args[1]);
		is_large = exit_stt > (unsigned int)INT_MAX;

		if (!valid || args_len > 10 || is_large)
		{
			write(STDERR_FILENO, "Invalid exit status\n", 20);
			data->status = 2;
			return (1);
		}
		data->status = exit_stt;
	}
	return (0);
}
