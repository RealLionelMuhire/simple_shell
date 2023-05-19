#include "shell.h"

/**
 * check_exec - it checks weather it is executable
 * @data: shell data containin all data
 * Return: 0 if it is not execitable, positive int otherwise
 */

int check_exec(sh_dt *data)
{
	struct stat st;
	int i = 0;
	char *str = data->args[0];

	while (str[i] && (str[i] != '.' || (str[i] == '.' &&
					str[i + 1] != '/')))
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
	pid_t pid, wpid;
	int state, run;
	(void) wpid;

	run = check_exec(data);
	if (run == -1)
		return (1);

	pid = fork();
	if (pid == 0)
		execve(data->args[0], data->args, data->env);
	else if (pid < 0)
	{
		perror(data->av[0]);
		return (1);
	}
	else
	{
		do {
			wpid = waitpid(pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->status = state / 256;
	return (1);
}
