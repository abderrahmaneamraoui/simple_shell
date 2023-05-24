#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 * Return: a negative num if s1 < s2, positive if s1 > s2 or zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	char *s11;
	char *s22;

	s11 = s1;
	s22 = s2;

	if (!s1 && !s2)
		return (0);

	if (!s1 || !s2)
		return (-1);

	while (*s11 == *s22)
	{
		if (*s11 == '\0')
			break;
		if (*s22 == '\0')
			break;
		s11 = s11 + 1;
		s22 = s22 + 1;
	}

	if (*s11 < *s22)
		return (*s11 - *s22);
	if (*s11 > *s22)
		return (*s11 - *s22);

	return (0);
}

/**
 * _strlen - get the length of a string
 * @s: the string
 * Return: the number of characters in the string minus the null char
 */
int _strlen(char *s)
{
	int len;

	len = 0;
	while (s && s[len] != '\0')
		len++;
	return (len);
}

/**
  * word_count - counts the number of words in a string seperated by a delim
  * @str: string to count the words
  * @delim: separator between words
  * Return: number of words
  */
int word_count(char *str, char *delim)
{
	int i, check = 0, count = 0;

	for (i = 0; str && str[i]; i++)
	{
		if ((str[i] == delim[0]) && check)
		{
			count++;
			check = 0;
		}
		else if (str[i] != delim[0])
			check = 1;
	}
	if (str && str[0])
		count++;

	return (count);
}

/**
 * _strcat - Concats two strings
 * @dest: The destination
 * @src: The source
 *
 * Return: The destination string
 */
char *_strcat(char *dest, char *src)
{
	char *write;
	char *s2;

	if (!src)
		return (dest);
	if (!dest)
		return (src);
	write = dest;
	s2 = src;
	for (; *write != '\0'; write++)
	{
	}
	for (; *s2 != '\0'; s2++)
	{
		*write = *s2;
		write++;
	}
	*write = '\0';
	return (dest);
}

/**
  * _strcpy - copy src into dest
  * @dest: destination for copied string
  * @src: string to copy
  * Return: copied string
  */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; i <= _strlen(src); i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}
