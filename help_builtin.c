#include "shell.h"

/**
 * help_shell - display help page for builtin commands
 */

void help_shell(void)
{
	_puts("\nShell version 1.0\n\n");
	_puts("Usage: ./hsh\n\n");
	_puts("Shell built in commands:\n\n");
	_puts("help\t\tView help information\n\n");
	_puts("env\t\tView the environment variables\n\n");
	_puts("setenv\t\tSet environment variables\n\n");
	_puts("unsetenv\t\tUnset environment variables\n\n");
	_puts("cd [dir]\tChange current working directory\n\n");
	_puts("exit\t\tExit the shell\n\n");
}
