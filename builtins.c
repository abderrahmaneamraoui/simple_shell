#include "shell.h"

/**
  * get_builtins - list of builtin commands
  * Return: double pointer holding list of commands
  */
char **get_builtins()
{
	char **builtins;

	builtins = do_mem(sizeof(char *) * 6, NULL);

	builtins[0] = "exit";
	builtins[1] = "cd";
	builtins[2] = "env";
	builtins[3] = "setenv";
	builtins[4] = "unsetenv";
	builtins[5] = NULL;

	return (builtins);
}

/**
 * env_builtin - Lists environment
 *  Return: 0 if successfull
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
	free_double_array(env);

	return (0);
}

/**
 * setenv_builtin - Set an environment variable
 * @tokens: the tokens for the command
 * Return: the return code
 */
int setenv_builtin(char **tokens)
{
	char *ret = NULL;

	if (!tokens[1] || !tokens[2])
	{
		my_error(tokens[0], 3001, NULL);
		return (1);
	}
	do_env(NULL, tokens[1]);

	ret = do_mem(_strlen(tokens[1]) + _strlen(tokens[2]) + 2, NULL);
	_strcat(ret, tokens[1]);
	_strcat(ret, "=");
	_strcat(ret, tokens[2]);
	do_env(ret, NULL);

	return (0);
}

/**
 * unsetenv_builtin - Unset an environment variable
 * @tokens: the tokens for the command
 * Return: the return code
 */
int unsetenv_builtin(char **tokens)
{

	if (!tokens[1])
	{
		my_error(tokens[0], 3002, NULL);
		return (1);
	}
	do_env(NULL, tokens[1]);

	return (0);
}


/**
 * cd_builtin - executes cd function, changes directory
 * @tokens: command input into prompt tokenized
 * Return: the exit status
 */
int cd_builtin(char **tokens)
{
	char *HOME = NULL, *templd;
	static char *lastdir;

	(void)HOME;
	if (!lastdir)
		lastdir = do_mem(100, NULL);
	templd = do_mem(100, NULL);
	if (tokens[1] && _strcmp(tokens[1], "-") == 0)
	{
		getcwd(templd, 100);
		chdir(lastdir);
		write(STDOUT_FILENO, lastdir, _strlen(lastdir));
		write(STDOUT_FILENO, "\n", 1);
		lastdir = templd;
	}
	else if (tokens[1])
	{
		getcwd(lastdir, 100);
		chdir(tokens[1]);
	}
	else
	{
		getcwd(lastdir, 100);
		chdir(get_env_val("HOME"));
	}
	return (0);
}
