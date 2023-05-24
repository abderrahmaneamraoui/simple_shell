#include "shell.h"

/**
 * handle_env_command - handles env command
 * Return: void
 * @param args An array of strings representing the arguments to the command.
 * The first argument should be the name of the command itself ("env").
 */

void handle_env_command(void)
{
char **env = environ;
while (*env)
{
printf("%s\n", *env++);
}
}

/**
 * execute_command - executes command
 * @args: arugmes
 * Return: void
 * @param args An array of strings representing the arguments to the command.
 * The first argument should be the name of the command itself.
 */
void execute_command(char **args)
{
pid_t pid;
int status;

char *command = args[0];
char *cmd_path = find_command_path(command);

if (cmd_path == NULL)
{
if (strcmp(command, "env") == 0)
{
handle_env_command();
}
else
{
fprintf(stderr, "%s: command not found\n", command);
}
return;
}



free(cmd_path);
}
