#include "shell.h"

/**
 * get_builtins - list builtins commands
 * Return: pointer holding list of commands
 */

char **get_builtins()
{
	char **builtins;

	builtins = do_mem(sizeof(char *) * 6, NULL);

	builtins[0] = "exit";
	builtins[1] = "env";
	builtins[2] = "setenv";
	builtins[3] = "unsetenv";
	builtins[4] = "cd";
	builtins[5] = NULL;

	return (builtins);
}

/**
 * env_builtin - prints environment
 * Return: 0 if successful
 */

int env_builtin(void)
{
	char **env;
	int i = 0, len = 0;

	env = get_env();
	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i = i + 1;
	}
	free_double(env);

	return (0);
}

/**
 * setenv - set environment variable
 * @args: the arguments for the command
 * Return: retrun code
 */

int setenv(char **args)
{
	char *ret = NULL;

	if (!args[1] || !args[2])
	{
		print_error(args[0], 3001, NULL);
		return (1);
	}
	do_env(NULL, args[1]);

	ret = do_mem(_strlen(args[1]) + _strlen(args[2]) + 2, NULL);
	_strcat(ret, args[1]);
	_strcat(ret, "=");
	_strcat(ret, args[2]);
	do_env(ret, NULL);

	return (0);
}

/**
 * unsetenv - Unset environment varibale
 * @args: argument for command
 * Return:return code
 */

int unsetenv(char **args)
{
	if (!args[1])
	{
		print_error(args[0], 3302, NULL);
		return (1);
	}
	do_env(NULL, args[1]);

	return (0);
}

/**
 * cd - executes cd function
 * @args: argguments for the command
 * Return: exit status
 */

int cd(char **args)
{
	char *HOME = NULL, *templd;
	static char *lastdir;

	(void)HOME;
	if (!lastdir)
		lastdir = do_mem(100, NULL);
	templd = do_mem(100, NULL);
	if (args[1] && _strcmp(args[1], "-") == 0)
	{
		getcwd(templd, 100);
		chdir(lastdir);
		write(STDOUT_FILENO, lastdir, _strlen(lastdir));
		write(STDOUT_FILENO, "\n", 1);
		lastdir = templd;
	}
	else if (args[1])
	{
		getcwd(lastdir, 100);
		chdir(token[1]);
	}
	else
	{
		getcwd(lastdir, 100);
		chdir(get_env_val("HOME"));
	}
	return (0);
}

