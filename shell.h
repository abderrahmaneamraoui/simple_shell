#ifndef SHELL_H
#define SHELL_H
// Include headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>
#include <fcntl.h>

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
void exit_shell(char **args);
void cd_shell(char **args);
int env_shell(void);
int clear_shell(char **args);
void free_token(char **ptr);
void free_last_input(void);
void _puts(char *str);
void _printerror(char *err);
int check_builtin(char **args);
int _strlen(const char *);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2);
char *_strstr(char *haystack, char *needle);
char *_strchr(char *s, char c);

#endif /* SHELL_H */
