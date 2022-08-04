#include "shell.h"

unsigned int _strlen(const char *s);
char *_strchr(char *s, int c);

/**
 * _strchr - searches for first occurence of char
 * in the string pointed to.
 * @s: pointer to null terminated string
 * @c: character to search for
 *
 * Return: pointer to located character
 */

char *_strchr(char *s, int c)
{
	char *isCharFind = NULL;

	if (s != NULL)
	{
		do
		{
			if (*s == (char)c)
			{
				isCharFind = s;
				break;
			}
		} while (*s++);
	}
	return (isCharFind);
}

/**
 * _strlen - gets legth of string
 * @s: string
 * Return: length
 */
unsigned int _strlen(const char *s)
{
	unsigned int count = 0;

	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}
