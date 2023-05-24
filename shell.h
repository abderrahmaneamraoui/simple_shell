#ifndef SHELL_H
#define SHELL_H
// Include headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LEN 1024
#define MAX_INPUT_LENGTH 1024
#define BUFFER_SIZE 1024
// Function prototypes
extern char **environ;

char *read_line(void);
char **parse_line(char *line);
void print_hello(void);
void print_prompt(void);
char **tokenize_input(char *input);
void execute_command(char **args);
char *custom_getline(void);
char **tokenize(char *line, char *delim);
int execute(char **args);
char *find_command_path(char *command);
#endif
