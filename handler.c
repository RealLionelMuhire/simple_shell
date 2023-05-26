#include "shell.h"

/*
 */
int handle_input(sh_dt *data, char *cmd)
{

	cmd = hash_hand(cmd);
	if (cmd == NULL)
		return (1);

	if (err_synt_checker(data, cmd) == 1)
	{
		data->status = 2;
		free(cmd);
		return (1);
	}
	cmd = replace_v(cmd, data);
	cmd_tok(data, cmd);
	free(cmd);
	data->count += 1;
	return (0);
}

void cleanup(sh_dt *data)
{
	 free_d(data);
}
