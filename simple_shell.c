#include "shell.h"

/**
* print_prompt - Prints shell prompt
*
* This function prints the shell prompt "#cisfun$ ".
*/
void print_prompt(void)
{
printf("#cisfun$ ");
}

/**
* tokenize_input - Tokenizes input string
* @input: Input string
*
* This function tokenizes the input string into an array of strings.
*
* Return: Array of strings
*/
char **tokenize_input(char *input)
{
char **tokens;
char *token;
int i = 0;

tokens = malloc(sizeof(char *) * MAX_INPUT_LENGTH);
if (tokens == NULL)
{
return (NULL);
}

token = strtok(input, " \t\n");
while (token != NULL)
{
tokens[i++] = token;
token = strtok(NULL, " \t\n");
}
tokens[i] = NULL;

return (tokens);
}

/**
* execute_command - Executes a command
* @args: Array of command arguments
*
* This function executes the command specified by the array of command
* arguments.
*/
void execute_command(char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid == 0)
{
execve(args[0], args, NULL);
perror("execve");
_exit(1);
}
else if (pid < 0)
{
perror("fork");
}
else
{

do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}

/**
* main - Shell entry point
*
* This function is the entry point for the shell program. It reads input
* from standard input, tokenizes it, and executes the specified command.
* @argc: Number of arguments
* @argv: list of arguments
* @envp: environment
* Return: Always 0
*/
int main(int argc, char **argv, char **envp)
{
	char *filename = NULL;

	get_prog_name(argv[0]);

	/* argc the right amount of arguments */
	if (argc > 2)
		return (-1);

	/* check if argv[1] is a file */
	if (argv && argv[1])
		filename = argv[1];
	/* signal handler */
	signal(SIGINT, signal_handler);
	/* initialize the environment */
	do_env((char *)envp, NULL);

	/* initialize the linum */
	linum(1);

	/* read, tokenize, execute loop */
	main_loop(filename);

	/* clean up */

	return (0);
}
