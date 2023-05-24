#include "shell.h"

/**
 * execute_builtin - execute builtins
 * @args: array
 * @bcase: which builtin to execute
 * Return: 0 Success, 1 Failure
 */

int execute_builtin(char **args, int bcase)
{
	int exit = 0;
	int i = 0;

		switch (bcase)
	{
	case 1:
	{
		if (args[1])
		{
			for (; args[1][i]; i++)
				if (!_isdigit(args[1][i]))
				{
					exit_shell(2, "numeric arguments only\n", exit);
				}
			exit = _atoi(args[1]);
		}
		exit_shell(2, "", exit);
		break;
	}
		case 2:
			return (cd_shell(args));
		case 3:
			return (env_shell());
		case 4:
			return (setenv(args));
		case 5:
			return (unsetenv(args));
	}
	return (0);
}


/**
 * access_check - checks if path or permission exists
 * @command: path to command
 * @arg: command
 * Return: exit
 */

int access_check(char *command, char *arg)
{
	int access = 0;

	access = access(command, F_OK);
	if (code)
	{
		print_error("Not found\n");
	}

	access = access(command, X_OK);
	if (access)
	{
		print_error("permission denied\n");
	}

	return (0);
}

/**
 * prep_execve - preps cmd
 * @arg: commnad to check
 * Return: command prepared for execve
 */

char *prep_execve(char *arg)
{
	char **envVars = NULL;
	char *command = NULL;
	char *cwd = NULL;
	char *path = NULL;
	int access = 0;

	cwd = do_mem(100, NULL);
	command = find_command_path(cwd, arg);
	access = access(command, F_OK);
	if (access)
	{
		envVars = read_line();
		path = parse_line(line, arg);
		command = find_command_path(path, arg);
		free_token(envVars);
	}
	return (command);
}

/**
 * exec_nb - execute function for non builtins
 * @args: STDIN tokenized
 * Return: 0 Success, Failute exit
 */

int exec_nb(char **args)
{
	char *command = NULL;
	pid_t cpid, wid;
	int status = 0, access = 0;

	command = prep_execve(args[0]);
	while ((access = access_check(command, args[0])))
		return (access);

	cpid = fork();

	if (cpid == -1)
		exit_shell("Fork failed");
	if (!cpid)
	{
		execve(command, args, (char * const *)env_shell());
		perror("");
		exit_shell("Couldn't execution\n");
	}
	else
	{
		do {
			wid = waitpid(cpid, &status, WUNTRACED);
			if (wid == -1)
			{
				perror("waitpid");
				exit_shell("");
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		do_mem(0, command);
	}
	return (status);
}

/**
 * search_shell - search for ;, &&, || operators
 * @args: array
 * Return: 0 if none, 1 if ;, 2 if &&, 3 if ||
 */

int search_shell(char **args)
{
	int i = 0;

	if (!args)
	{
		return (0);
	}
	for (i = 0; args[i]; i++)
	{
		if (args[i][0] == ';')
			return (1);
		if (args[i][0] == '&' && args[i][1] && args[i][1] == '&')
			return (2);
		if (args[i][0] == '|' && args[i][1] && args[i][1] == '|')
			return (3);
	}
	return (0);
}
