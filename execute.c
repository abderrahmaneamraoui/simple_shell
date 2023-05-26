#include "shell.h"

/**
  * exec_builtin - execute function for builtins
  * @tokens: STDIN tokenized
  * @bcase: which builtin to execute
  * Return: 0 if succesful 1 if it fails
  */
int exec_builtin(char **tokens, int bcase)
{
	int exit = 0;
	int i = 0;

	switch (bcase)
	{
	case 1:
	{
		if (tokens[1])
		{
			for (; tokens[1][i]; i++)
				if (!_isdigit(tokens[1][i]))
				{
					do_exit(2, "numeric arguments only\n", exit);
				}
			exit = _atoi(tokens[1]);
		}
		do_exit(2, "", exit);
		break;
	}
	case 2:
		return (cd_builtin(tokens));
	case 3:
		return (env_builtin());
	case 4:
		return (setenv_builtin(tokens));
	case 5:
		return (unsetenv_builtin(tokens));
	}
	return (0);
}

/**
 * check_access - checks if path exists or if permission exists for command
 * @comm: path to command
 * @token: command
 * Return: exit condition
 */
int check_access(char *comm, char *token)
{
	int accessCode = 0;

	accessCode = access(comm, F_OK);
	if (accessCode)
	{
		my_error(token, 2, NULL);
		return (2);
	}

	accessCode = access(comm, X_OK);
	if (accessCode)
	{
		my_error(token, 126, NULL);
		return (126);
	}
	return (0);
}

/**
 * prep_execve - preps cmd by checking current path and then the PATH for cmd
 * @token: commmand to check
 * Return: command preped for execve
 */
char *prep_execve(char *token)
{
	char **envVars = NULL;
	char *comm = NULL;
	char *cwd = NULL;
	char *path = NULL;
	int accessCode = 0;

	cwd = do_mem(100, NULL);
	comm = get_full_command(cwd, token);
	accessCode = access(comm, F_OK);
	if (accessCode)
	{
		envVars = get_path();
		path = find_path(envVars, token);
		comm = get_full_command(path, token);
		free_double_array(envVars);
	}
	return (comm);
}
/**
  * exec_nb - execute function for non builtins
  * @tokens: STDIN tokenized
  * Return: the exit status of the program, 0 if successful
  */
int exec_nb(char **tokens)
{
	char *comm = NULL;
	pid_t cpid, wid;
	int status = 0, accessCode = 0;

	comm = prep_execve(tokens[0]);
	while ((accessCode = check_access(comm, tokens[0])))
		return (accessCode);

	cpid = fork();

	if (cpid == -1)
		do_exit(2, "Fork failed", EXIT_FAILURE);
	if (!cpid)
	{
		execve(comm, tokens, (char * const *)get_env());
		perror("");
		do_exit(2, "Couldn't exec", EXIT_FAILURE);
	}
	else
	{
		do {
			wid = waitpid(cpid, &status, WUNTRACED);
			if (wid == -1)
			{
				perror("waitpid");
				do_exit(STDERR_FILENO, "", EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		do_mem(0, comm);
	}
	return (status);
}

/**
  * search_ops - search for ;, &&, || operators
  * @tokens: tokens from std input
  * Return: 0 if none, 1 if ';', 2 if '&&' 3 if '||'
  */
int search_ops(char **tokens)
{
	int i = 0;

	if (!tokens)
	{
		return (0);
	}
	for (i = 0; tokens[i]; i++)
	{
		if (tokens[i][0] == ';')
			return (1);
		if (tokens[i][0] == '&' && tokens[i][1] && tokens[i][1] == '&')
			return (2);
		if (tokens[i][0] == '|' && tokens[i][1] && tokens[i][1] == '|')
			return (3);
	}
	return (0);
}
