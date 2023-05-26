#include "shell.h"

/**
 * check_builtin - checks that the command is a builtin
 * @args: arguments array
 * Return: 1 is builtin, 0 if not
 */

int check_builtin(char **args)
{
	if (!args[0])
		return (0);
	if (!_strcmp(args[0], "exit"))
		exit_shell(args);
	else if (!_strcmp(args[0], "env"))
		env_shell();
	else if (!_strcmp(args[0], "setenv"))
		setenv(args);
	else if (!_strcmp(args[0], "unsetenv"))
		unsetenv(args);
	else if (!_strcmp(args[0], "cd"))
		cd_shell(args);
	/* Add check for help */
	/* Add check for clear */
	else
		return (0);
	return (1);
}
