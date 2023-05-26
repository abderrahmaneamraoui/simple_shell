/**
 * Command Execution Program
 *
 * This program provides functions to search for a command in the directories
 * listed in the PATH environment variable and execute the command if found.
 *
 * Author: Abderahmane Amraoui
 * Date:  18/05/2023
 */
#include "shell.h"

/**
 * Searches for the command in the directories listed in PATH.
 *
 * @param command The command to search for.
 *
 * @return The full path to the command if found, or NULL otherwise.
 */
char *find_command_path(char *command)
{
char *path = getenv("PATH");
if (path == NULL)
{
return (NULL);
}

char *dir = strtok(path, ":");
while (dir != NULL)
{
char *cmd_path = malloc(strlen(dir) + strlen(command) + 2);
if (cmd_path == NULL)
{
return (NULL);
}
sprintf(cmd_path, "%s/%s", dir, command);
if (access(cmd_path, X_OK) == 0)
{
return (cmd_path);
}
free(cmd_path);

dir = strtok(NULL, ":");
}

return (NULL);
}
/**
 * Executes a command by searching for the command in
 * the directories listed in PATH.
 *
 * @param args an array of strings representing the arguments to the command.
 *             The first argument should be the name of the command itself.
 *
 * @return void
 */
void execute_command(char **args)
{
pid_t pid;
int status;
char *command = args[0];
char *cmd_path = find_command_path(command);
if (cmd_path == NULL)
{
fprintf(stderr, "%s: command not found\n", command);
return;
}

pid = fork();
if (pid == 0)
{
execv(cmd_path, args);
perror("execv");
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

free(cmd_path);
}
/**
 * The main function of the program.
 *
 * @return zero onsuccess
 */
int main(void)
{

char *args[] = { "ls", "-l", NULL };
execute_command(args);

return (0);
}
