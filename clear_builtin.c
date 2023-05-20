#include "shell.h"

/**
 * clear_shell - clear terminal screen
 * @args: array of arguments
 * Return: 1 Successs, 0 to exit
 */

int clear_shell(char **args)
{
	(void)args;

	_puts("\033[2J\033[H");
	return (1);
}
