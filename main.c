#include "shell.h"

/**
 * main - entry point of a simple shell
 * @av: arguments vector
 * @argc: argments counts
 * Return: always 0 at sucess otherwise specified
 */

int main(int argc, char **av)
{
	sh_dt data;
	char *cmd;
	int ret;
	(void) argc;

	signal(SIGINT, sigHandler);
	data_init(av, &data);
	while (1)
	{
		PRINT("$ ");
		cmd = get_input(&ret);
		if (ret != -1)
		{
			cmd = hash_hand(cmd);
			if (cmd == NULL)
				continue;

			if (err_synt_checker(&data, cmd) == 1)
			{
				data.status = 2;
				free(cmd);
				continue;
			}
			cmd = replace_v(cmd, &data);
			cmd_tok(&data, cmd);
			free(cmd);
			data.count += 1;
		}
		else
		{
			free(cmd);
			handle_exit(&data);
			/*break;*/
		}
	}

	/*free_d(&data);
	if (data.status < 0)
		return (255);*/
	return (data.status);
}
