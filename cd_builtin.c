#include "shell.h"

/**
 * cd_shell - change the working directory of the shell
 * @args: arguments
 * Return: void
 */
void cd_shell(char **args)
{
	char *dir = args[1];
	int ret;

	if (dir == NULL)
	{
		dir = _getenv("HOME");
		if (dir == NULL)
		{
			_puts("cd: HOME directory not found\n");
			return;
		}
	}

	ret = chdir(dir);
	if (ret == -1)
	{
		perror("cd");
	}
}
