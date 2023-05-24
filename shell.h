#ifndef SHELL_H
#define SHELL_H
/* Include headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>
#include <fcntl.h>
#include <dirent.h>
#include <stddef.h>

#define MAX_LEN 1024
#define MAX_INPUT_LENGTH 1024
#define BUFFER_SIZE 1024

/**
 * struct list_p - singly linked list
 * @ptr: a malloced address
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton shell project
 */
typedef struct list_p
{
	void *ptr;
	struct list_p *next;
} list_t;

/**
 * struct list_p2 - singly linked list
 * @ptr: a malloced string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton shell project
 */
typedef struct list_p2
{
	char *ptr;
	struct list_p2 *next;
} list_s;

/* Function prototypes */
extern char **environ;

char *read_line(void);
char **parse_line(char *line);
void print_hello(void);
void print_prompt(void);
char **tokenize_input(char *input);
char *find_command_path(char *command);
void execute_command(char **args);
char *custom_getline(void);
char **tokenize(char *line, char *delim);
int **get_builtins();
int env_builtin(void);
int setenv(char **args);
int unsetenv(char **args);
int cd(char **args);
char **get_path();
char *get_env_val(char *name);
char **get_env();
char **do_env(char *x, char *y);
void exit_shell(int fd, char *msg, int code);
int execute(char **args);
int exec_nb(char **args);
int search_shell(char **args);
int exec_builtin(char **args, int bcase);
int access_check(char *command, char *arg);
char *prep_execve(char *arg);
char *read_textfile(char *filename);
void free_token(char **ptr);
void free_last_input(void);
void _puts(char *str);
void _printerror(char *err);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strstr(char *haystack, char *needle);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(const char *);
int _putchar(char);
unsigned int _strspn(char *s, char *accept);
int _isdigit(int c);
char *_memset(char *s, char b, int n);
int _atoi(char *s);
size_t __list_len(list_t *h);
list_t *__add_node(list_t **head, void *ptr);
list_t *__add_node_end(list_t **head, void *ptr);
void __free_list(list_t *head);
char **arrayify(list_s *head);
list_s *listifY(char **arr);
void free_double(char **list);
void free_list_full(list_s *head);
list_s *get_node_at_index(list_s *head, unsigned int index);
list_s *insert_node_at_index(list_s **head, unsigned int idx, char *ptr);
int delete_node_at_index(list_s **head, unsigned int index);

#endif
