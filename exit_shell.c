#include "shell.h"

/**
 * exit_shell - Exit the shell exit status
 * @args: Arguments
 * Return: NULL
 */

void exit_shell(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = _atoi(args[1]);
	}

	free_token(args);
	free_last_input();
	exit(status);
}
