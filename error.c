#include "shell.h"

/**
 * _puts - Prints string to standard output stream
 * @str: string
 * Return: void
 */

void _puts(char *str)
{
	size_t len;
	ssize_t number_written;

	len = _strlen(str);
	number_written = write(STDOUT_FILENO, str, len);
	if (number_written == -1)
	{
		perror("write");
	}
}

/**
 * _printerror - Prints error message to standrad error stream
 * @err: Error message
 * Return: void
 */

void _printerror(char *err)
{
	size_t len;
	ssize_t number_written;

	len = _strlen(err);
	number_written = write(STDERR_FILENO, err, len);
	if (number_written == -1)
	{
		perror("write");
	}
}
