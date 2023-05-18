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
char **tokens = malloc(sizeof(char *) * MAX_INPUT_LENGTH);
if (tokens == NULL)
{
return (NULL);
}

int i = 0;
char *token = strtok(input, " \t\n");
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
*
* Return: Always 0
*/
int main(void)
{
char input[MAX_INPUT_LENGTH];
char **args;

while (1)
{
print_prompt();

if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
{
printf("\n");
break;
}

args = tokenize_input(input);
if (args == NULL)
{
fprintf(stderr, "Failed to tokenize input\n");
continue;
}

if (args[0] == NULL)
{
free(args);
continue;
}

execute_command(args);

free(args);
}

return (0);
}
