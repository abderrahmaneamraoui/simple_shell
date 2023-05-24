#include "shell.h"

/**
 * execute_single - executes single command
 * @args: args for command
 * Return: return value of execuete as int
 */

int execute_single(char **args)
{
	char **builtins = NULL;
	int works = 1, i = 0, checkBuiltin = 0;

	if (!args || !args[0])
		return (0);
	builtins = get_builtins();

	for (i = 0; builtins[i]; i++)
		if (_strcmp(builtins[i], args[0]) == 0)
		{
			checkBuiltin = i + 1;
			break;
		}

	if (checkBuiltin && args)
		works = exec_builtin(args, checkBuiltin);
	else if (args)
		works = exec_nb(args);
	return (works);
}

/**
 * get_next_commands - gets teh args after first && || ;
 * @args: args of the command
 * Return: args after teh first && ||;
 */

char **get_next_commands(char **args)
{
	char **arguments = NULL;
	int commandSize = 0, retSize = 0, i = 0;

	if (!args || !(args[0]))
		return (NULL);
	commandSize = sizeof_command(args);
	if (!(args[commandSize]) || !(args[commandSize + 1]))
		return (NULL);
	while (args[commandSize + 1 + retSize])
		retSize++;

	arguments = do_mem(sizeof(char *) * (retSize + 1), NULL);
	for (i = 0; i < retSize; i++)
	{
		arguments[i] = do_mem(_strlen(args[commandSize + 1 + i]) + 1, NULL);
		_strcpy(arguments[i], args[commandSize + 1 + i]);
	}
	arguments[i] = NULL;
	return (arguments);
}

/**
 * get_current_command - gets the args before && || or ;
 * @args: args for command
 * Return: teh command till the first && || or ;
 */

char **get_current_command(char **args)
{
	char **arguments = NULL;
	int commandSize = 0, i = 0;

	if (!args || !(args[0]))
		return (NULL);

	commandSize = sizeof_command(args);
	if (!commandSize)
		return (NULL);
	arguments = do_mem(sizeof(char *) * (commandSize + 1), NULL);
	for (i = 0; i < commandSize; i++)
	{
		arguments[i] = do_mem(_strlen(args[i]) + 1, NULL);
		_strcpy(arguments[i], args[i]);
	}
	arguments[i] = NULL;

	return (arguments);
}

/**
 * execute - main execute function
 * @args: arguments
 * Return: Success int
 */

int execute(char **args)
{
	int works = 0, op = 0;
	char **head = NULL;
	char **tail = NULL;

	op = search_shell(args);
	head = get_current_command(args);
	tail = get_next_commands(args);

	while (1)
	{
		if (!head || !(head[0]))
			return (works);

		works = execute_single(head);

		if (op == 3 && !works)
			return (works);

		op = search_shell(tail);
		head = get_current_command(tail);
		tail = get_next_commands(tail);
	}

	return (1);
}
