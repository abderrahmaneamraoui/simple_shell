#include "shell.h"

/**
 * free_token - frees allocated memory granted dynamically by tokenize
 * @ptr: pointer to allocated memory
 * Return: void
 */

void free_token(char **ptr)
{
	int i;

	for (i = 0; ptr[i]; i++)
		free((ptr[i]));
	free(ptr);
}

/**
 * free_last_input - Frees the last input of user
 * should be called after input string is no longer needed
 */

void free_last_input(void)
{
	free(last_input);
	last_input = NULL;
}

