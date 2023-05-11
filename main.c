#include "shell"

/**
 * main - entry point of a simple shell
 * av - arguments vector
 * @argc - argments counts
 * Return: always 0 at sucess otherwise specified
 */

int main(char **av, int argc)
{
	sh_dt data;
	char *cmd;
	int ret;

	while (1)
	{
		PRINT("$ ");
		cmd = get_input(&ret);

		if (ret != -1)
		{
			cmd = hash_hand(cmd);
			if (cmd == NULL)
				continue;

			if (err_synt_checker(data, cmd) == 1)
			{
				data->status = 2;
				free(cmd);
				continue;
			}
		}
		else
		{
			free(cmd)
			break;
		}


	}
}
