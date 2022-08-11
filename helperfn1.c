#include "shell.h"

int get_len(const char *s);
char *cpy_str(char *str1, const char *str2);
char *cat_str(char *str1, const char *str2);
char *ncat_str(char *str1, const char *str2, size_t n);


/**
 * get_len - gets length of string
 * @s: pointer to string
 *
 * Return: length of string
 */

int get_len(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len];)
		len++;
	return (len);
}

/**
 * cpy_str - copies string pointed to by str2 to str1 including null byte
 * @str1: pointer to destination of copied str
 * @str2: pointer to source str
 *
 * Return: pointer to str1
 */

char *cpy_str(char *str1, const char *str2)
{
	size_t i;

	for (i = 0; str2[i] != '\0'; i++)
		str1[i] = str2[i];
	str1[i] = '\0';
	return (str1);
}

/**
 * cat_str - concatenates 2 str
 * @str1: pointer to dest
 * @str2: pointer to src
 *
 * Return: pointer to concat str
 */

char *cat_str(char *str1, const char *str2)
{
	char *temp1 = str1;
	const char *temp2 = str2;

	while (*temp1 != '\0')
		temp1++;
	while (*temp2 != '\0')
		*temp1++ = *temp2++;
	*temp1 = '\0';
	return (str1);
}

/**
 * ncat_str - concatenates 2 strings where n number of bytes are
 * copied from source
 * @str1: string 1
 * @str2: string 2
 * @n: number of bytes
 *
 * Return: concatenated string
 */

char *ncat_str(char *str1, const char *str2, size_t n)
{
	int len = get_len(str1);
	int i;

	for (i = 0; i < n && str2[i] != '\0'; i++)
		str2[len + i] = str2[i];
	str1[len + i] = '\0';

	return (str1);
}

