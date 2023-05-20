#include "shell.h"

/**
 * setenv - Sets environemnt variable value
 * @args: name and value of the environment variable
 * Return: 0
 */

int setenv(char **args)
{
	char *name, *value;

	if (args[1] == NULL || args[2] == NULL)
	{
		_printerror("Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	name = args[1];
	value = args[2];

	if (setenv(name, value, 1) != 0)
	{
		_printerror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * unsetenv - Unsets environment variable value
 * @args: name of environment variable
 * Return: 0
 */

int unsetenv(char **args)
{
	char *name;

	if (args[1] == NULL)
	{
		_printerror("Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	name = args[1];

	if (unsetenv(name) != 0)
	{
		_printerror("unsetenv");
	}
	return (0);
}
