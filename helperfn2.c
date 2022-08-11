#include "shell.h"

char *strchr_fnc(char *s, char c);
int initlen_sub(char *s, char *acc);
int cmp(char *str1, char *str2);
int ncmp(const char *str1, const char *str2m size_t n);

/**
 * strchr_fnc - locates charin str
 * @s: stringto be searched
 * @c: the charcter
 *
 * Return: pointer to first occurence
 */

char *strchr_fnc(char *s, char c)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == c)
			return (s + i);
	}

	return (NULL);
}

/**
 * initlen_sub - gets lenof prefixed string
 * @s: string
 * @acc: prefix to be measured
 *
 * Return: umber of bytes in s which consists of bytes from acc
 */

int initlen_sub(char *s, char *acc)
{
	int bytes = 0, i;

	while (*s)
	{
		for (i = 0; acc[i]; i++)
		{
			if (*s == acc[i])
			{
				bytes++;
				break++;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * cmp - compares 2 strings
 * @str1: string 1
 * @str2: string 2
 *
 * Return: positive byte diff if str1 > str2
 *	0 if str1 = str2
 *	Negatv byte diff if str2 > str1
 */

int cmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		*str1++;
		*str2++;
	}
	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * ncmp  - compares 2 strings upto n bytes
 * @str1: string 1
 * @str2: string 2
 * @n: first n bytes to compre
 *
 * Return: less than 0 if str1 is shorter than str2
 *	0 if str1 and str2 match
 *	Greater than 0 if str1 is longer than str2
 */

int ncmp(const char *str1, const char *str2, size_t n)
{
	int i;

	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[i] > str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] < str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
