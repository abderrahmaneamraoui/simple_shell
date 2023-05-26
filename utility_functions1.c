#include "shell.h"

/**
  * _atoi - converst a string to an integer
  * @s: string to be converted
  * Return: integers in a string
  */

int _atoi(char *s)
{
	int num, len, numcount, mult, x, neg;

	len = 0;
	x = 0;
	numcount = 0;
	mult = 1;
	neg = 1;
	num = 0;

	while (s[len] != '\0')
	{
		if (s[len] >= '0' && s[len] <= '9')
		{
			numcount++;
			if (!(s[len + 1] >= '0' && s[len + 1] <= '9'))
				break;
		}
		len++;
	}
	for (; numcount > 1; numcount--)
		mult *= 10;
	for (; x <= len; x++)
	{
		if (s[x] == '-')
			neg *= -1;
		else if (s[x] <= '9' && s[x] >= '0')
		{
			num += (s[x] - '0') * mult * neg;
			mult /= 10;
		}
	}
	return (num);
}

/**
  * sizeof_command - returns the size of command, breaks if it hits &&, ||, ;
  * @tokens: standard input tokenized
  * Return: the size of the command
  */
int sizeof_command(char **tokens)
{
	int i = 0;

	if (!tokens)
		return (0);
	for (i = 0; tokens[i]; i++)
	{
		if (tokens[i][0] == '&' && tokens[i][1] == '&')
			break;
		if (tokens[i][0] == '|' && tokens[i][1] == '|')
			break;
		if (tokens[i][0] == ';')
			break;
	}
	return (i);
}

/**
 * _isdigit - check for a digit (0 through 9)
 * @c: digit checked
 * Return: 1 if c is a digit returns 0 otherwise
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * has_newline - checks for \n or EOF and returns the index
 * @input: input read from read function in getline
 * Return: the size of command when it reaches \n or EOF
 */
int has_newline(char *input)
{
	int i;

	for (i = 0; input && input[i]; i++)
	{
		if (input[i] == '\n')
			return (i);
	}

	return (i);
}

/**
 * shiftbuffer - shifts the buffer to the next command after \n
 *  @input: input from standard input
 *  @newline_index: where there is a new line or EOF
 *  @filled: size filled to
 */
void shiftbuffer(char *input, int newline_index, int filled)
{
	int i = newline_index;
	int j = 0;

	for (; i < filled; i++, j++)
	{
		input[j] = input[i];
	}

	for (; j < 4096; j++)
	{
		input[j] = '\0';
	}
}
