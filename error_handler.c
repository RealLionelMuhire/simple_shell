#include "shell.h"

/**
 * get_err - calls and error message based to the error value passed
 * @data: data structure that contains arguments
 * @val_err: error value
 * Return: error type
 */
int get_err(sh_dt *data, int val_err)
{
	char *error = NULL;

	if (val_err == -1)
		error = error_env(data);
	else if (val_err == 126)
		error = error_path_126(data);
	else if (val_err == 127)
		error = error_not_found(data);
	else if (val_err == 2)
	{
		if (_strcmp("exit", data->args[0]) == 0)
			error = error_exit_shell(data);
		else if (_strcmp("cd", data->args[0]) == 0)
			error = error_get_cd(data);
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	data->status = val_err;
	return (val_err);
}
