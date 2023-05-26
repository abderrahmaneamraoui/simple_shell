#include "shell.h"

/**
 * _getchar - get a character
 * Return: the int value of the character or EOF
 */
int _getchar(void)
{
	char c;

	return (read(0, &c, 1) == 1 ? (unsigned char) c : EOF);
}
