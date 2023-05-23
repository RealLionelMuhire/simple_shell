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
		error = err_p_126err_p_126(data);
	else if (val_err == 127)
		error = err_n_found(data);
	else if (val_err == 2)
	{
		if (_strcmp("exit", data->args[0]) == 0)
			error = err_exit_sh(data);
		else if (_strcmp("cd", data->args[0]) == 0)
			error = err_cd(data);
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	data->status = val_err;
	return (val_err);
}

/**
 * cat_msg - it concatenates  the err msg for cd
 *
 * @data: data of shells
 * @msg: printout message
 * @err: error output
 * @ver_str: count lines
 * Return: error message
 */
char *cat_msg(sh_dt *data, const char *msg, char *err, const char *ver_str)
{
	_sprintf(err, "%s: %s: %s%s", data->av[0], ver_str, data->args[0], msg);
	if (data->args[1][0] == '-')
		_sprintf(err + _strlen(err), "-%c", data->args[1][1]);
	else
		_strcat(err, data->args[1]);

	_strcat(err, "\n");
	return (err);
}

/**
 * err_cd - error message for cd command in get_cd
 * @data: shell data related directory
 * Return: Error message
 */
char *err_cd(sh_dt *data)
{err_exit_sh
	char *count_str = _itoa(data->count), *error_msg;
	const char *msg = (datash->args[1][0] == '-') ?
		": Illegal option " : ": can't cd to ";
	int total_len = _strlen(data->av[0]) + _strlen(data->args[0]) +
		_strlen(count_str) + _strlen(msg) + strlen(data->args[1]) + 5;

	error_msg = malloc(sizeof(char) * (total_len + 1));
	if (error_msg == NULL)
	{
		free(count_str);
		return (NULL);
	}

	cat_msg(data, msg, error_msg, count_str);
	free(count_str);

	return (error_msg);
}


/**
 * err_n_found - generic error message for command not found
 * @data: data relevant (counter, arguments)
 * Return: Error message
 */
char *err_n_found(sh_dt *data)
{
	char *counter_str = _itoa(data->count);
	int total_length = _strlen(data->av[0]) + _strlen(counter_str) +
		_strlen(data->args[0]) + 16;

	char *error_msg = malloc(sizeof(char) * (total_length + 1));

	if (error_msg == NULL)
	{
		free(counter_str);
		return (NULL);
	}

	_sprintf(error_msg, "%s: %s: %s: not found\n", data->av[0],
			counter_str, data->args[0]);
	free(counter_str);

	return (error_msg);
}

/**
 * err_exit_sh - the error message for exit shell
 * @data: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *err_exit_sh(sh_dt *data)
{
	char *counter_str = _itoa(data->count);
	int total_length = _strlen(data->av[0]) + _strlen(counter_str) +
		_strlen(data->args[0]) + _strlen(data->args[1]) + 23;

	char *error_msg = malloc(sizeof(char) * (total_length + 1));

	if (error_msg == NULL)
	{
		free(counter_str);
		return (NULL);
	}

	_sprintf(error_msg, "%s: %s: %s: Illegal number: %s\n", data->av[0],
			counter_str, datash->args[0], datash->args[1]);
	free(counter_str);

	return (error_msg);
}
