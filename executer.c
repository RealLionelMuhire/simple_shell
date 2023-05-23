#include "shell.h"


/**
 * blt_cmd_h - handles builtins and commands
 * @data: struct
 * Return: builtin if it is passed otherwise commands
 */
int blt_cmd_h(sh_dt *data)
{
	int (*bltn)(sh_dt *data) = _builtin(data->args[0]);

	if (data->args[0] == NULL)
	{
		return (1);
	}

	return ((bltn != NULL) ? bltn(data) : exec_cmd(data));

}

/**
 * check_exec - it checks weather it is executable
 * @data: shell data containin all data
 ** Return: 0 if it is not execitable, positive int otherwise
 */

int check_exec(sh_dt *data)
{
	struct stat st;
	int i = 0;
	char *str = data->args[0];

	if (str == NULL)
		return (0);


	while (str[i] != '\0' &&
		       (str[i] != '.' ||
		(str[i] == '.' && str[i + 1] != '/')))
	{
		if (str[i] == '/')
		{
			if (str[i + 1] != '.')
			{
				i++;
				break;
			}
			i++;
			break;
		}
		i++;
	}
	if (i == 0)
		return (0);

	if (stat(str + i, &st) == 0)
		return (i);

	PRINT_ERR(": Permission denied\n");
	return (-1);
}

/**
 * exec_cmd - it executes and run cmd lines
 * @data: shell containing data
 * Return: 1 on success
 */
int exec_cmd(sh_dt *data)
{
	char p;
	pid_t pid, wpid;
	int state, run;
	(void) wpid;

	run = check_exec(data);
	if (run == -1)
		return (1);

	if (run == 0)
	{
		p = loc_exec(data->args[0], data->env);
		if (err_check(p, data) == 1)
		{
			free(p);
			return (1);
		}
	}


	pid = fork();
	if (pid == 0)
	{
		p = (run == 0) ? loc_exec(data->args[0], data->env) : data->args[0];
		execve(p + run, data->args, data->env);
	}
	else if (pid < 0)
	{
		perror(data->av[0]);
		free(p);
		return (1);
	}
	else
	{
		do {
			wpid = waitpid(pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->status = state / 256;
	free(p);
	return (1);
}

