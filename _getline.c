#include "shell.h"

/**
 * _getline - reads from STDIN the user input, storing the in the cmd.
 * @cmd: line input.
 * Return: 1 at success -1 on failure.
 */

int _getline(char *cmd)
{
	char *c_ptr, *end_ptr, c;
	size_t size = BUFSIZE, rd_byt, length, n_size;

	cmd = malloc(BUFSIZE);
	if (!cmd)
		return (-1);
	if (isatty(STDIN_FILENO))
		PRINT("$ ");
	fflush(stdout);

	for (c_ptr = cmd, end_ptr = cmd + size;;)
	{
		rd_byt = read(STDIN_FILENO, &c, 1);
		if (!rd_byt)
		{
			free(cmd);
			exit(0);
		}
		*c_ptr++ = c;
		if (c == '\n')
		{
			*c_ptr = '\0';
			return (1);
		}
		if (c_ptr + 2 >= end_ptr)
		{
			n_size = size * 2;
			length = c_ptr - cmd;
			cmd = _realloc(cmd, BUFSIZE, n_size);
			if (!cmd)
				return (-1);
			size = n_size;
			end_ptr = cmd + size;
			c_ptr = cmd + length;
		}
	}

}
