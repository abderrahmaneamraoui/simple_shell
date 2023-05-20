#include "shell.h"

/**
 * _strlen - returns length of string
 * @s: stirng to check
 * Return: length of string
 */

int _strlen(const char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}

	return (len);
}

/**
 * _strcmp - compare two strings
 * @s1: one string
 * @s2: second string
 * Return: int that tells num of spaces in between
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (*(s1 + i) == *(s2 + i) && *(s1 + i))
		i++;

	if (*(s2 + i))
		return (*(s1 + i) - *(s2 + i));
	else
		return (0);
}

/**
 * *_strstr - locate and return pointer to first occurence of substring
 * @haystack: string to search
 * @needle: target substirng to search for
 * Return: poniter to index of string at first occurence of whole substring
 */

char *_strstr(char *haystack, char *needle)
{
	int i = 0, j, x;

	if (needle[0] == '\0')
		return (haystack);

	while (haystack[i] == needle[0])
	{
		if (haystack[i] == needle[0])
		{
			x = i, j = 0;
			while (needle[j] != '\0')
			{
				if (haystack[x] == needle[j])
					x++, j++;
				else
					break;
			}
			if (needle[j] == '\0')
			{
				return (haystack + i);
			}
		}
		i++;
	}
	return (0);
}

/**
 * _strchr - locate first occurenece of char in string and returns pointer
 * @s: stirng to search
 * @c: target charcater
 * Return: pointer to that charcater in string
 */

char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] != '\0' && s[i] != c)
		i++;

	if (s[i] == c)
		return (&s[i]);
	else
		return (0);
}

