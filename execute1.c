#include "shell.h"

/**
 * exec_single - execute a single command
 * @tokens: the tokens for a single command
 * Return: int return value of the exec
 */
int exec_single(char **tokens)
{
	char **builtins = NULL;
	int works = 1, i = 0, checkBuiltIn = 0;

	if (!tokens || !tokens[0])
		return (0);
	builtins = get_builtins();

	for (i = 0; builtins[i]; i++)
		if (_strcmp(builtins[i], tokens[0]) == 0)
		{
			checkBuiltIn = i + 1;
			break;
		}

	if (checkBuiltIn && tokens)
		works = exec_builtin(tokens, checkBuiltIn);
	else if (tokens)
		works = exec_nb(tokens);
	return (works);
}

/**
 * get_next_commands - gets the tokens after the first && || or ;
 * @tokens: the tokens for the current command segment
 * Return: the tokens after the first && || ;, or NULL
 */
char **get_next_commands(char **tokens)
{
	char **extokens = NULL;
	int commandSize = 0, retSize = 0, i = 0;

	if (!tokens || !(tokens[0]))
		return (NULL);
	commandSize = sizeof_command(tokens);
	if (!(tokens[commandSize]) || !(tokens[commandSize + 1]))
		return (NULL);
	while (tokens[commandSize + 1 + retSize])
		retSize++;

	extokens = do_mem(sizeof(char *) * (retSize + 1), NULL);
	for (i = 0; i < retSize; i++)
	{
		extokens[i] = do_mem(_strlen(tokens[commandSize + 1 + i]) + 1, NULL);
		_strcpy(extokens[i], tokens[commandSize + 1 + i]);
	}
	extokens[i] = NULL;
	return (extokens);
}

/**
 * get_current_command - gets the command before && || or ;
 * @tokens: the tokens for the current command segment
 * Return: the command up until the first occurence of && || ; or NULL
 */
char **get_current_command(char **tokens)
{
	char **extokens = NULL;
	int commandSize = 0, i = 0;

	if (!tokens || !(tokens[0]))
		return (NULL);
	/* split tokens into separate commands if ;,&&,|| exist */
	commandSize = sizeof_command(tokens);
	if (!commandSize)
		return (NULL);
	extokens = do_mem(sizeof(char *) * (commandSize + 1), NULL);
	for (i = 0; i < commandSize; i++)
	{
		extokens[i] = do_mem(_strlen(tokens[i]) + 1, NULL);

		_strcpy(extokens[i], tokens[i]);
	}
	extokens[i] = NULL;

	return (extokens);
}

/**
  * execute - main execute function
  * @tokens: STDIN tokenized
  * Return: int if succesful
  */
int execute(char **tokens)
{
	int works = 0, op = 0;
	char **head = NULL;
	char **tail = NULL;

	op = search_ops(tokens);
	head = get_current_command(tokens);
	tail = get_next_commands(tokens);

	while (1)
	{
		if (!head || !(head[0]))
			return (works);

		works = exec_single(head);

		if (op == 3 && !works)
			return (works);
		if (op == 2 && works)
			return (works);

		op = search_ops(tail);
		head = get_current_command(tail);
		tail = get_next_commands(tail);

	}
	return (1);
}
