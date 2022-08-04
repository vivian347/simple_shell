#include "shell.h"

int _strcmp(const char *str1, const char *str2);
char *_path(char *com);
char *_strcat(char *str1, char *str2);
char *_strncat(char *str1, char *str2, int n);

/**
 * _strcmp - compares 2 strings
 * @str1: first string
 * @str2: 2nd string
 *
 * Return: 0 if equal
 */

int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

/**
 * _path - gets the path
 * @com: the command/file
 * Return: path
 */
char *_path(char *com)
{
	struct stat buff;
	char *path = NULL;
	char *token = NULL;
	char del[2] = ":";
	char *cwd = getcwd(NULL, 0);
	char **pth = malloc(MAX_SIZE);
	int i;
	char ch = '/';

	path = getenv("PATH");
	token = strtok(path, del);
	if (pth == NULL)
		i = 0;
	while (token)
	{
		pth[i] = token;
		token = strtok(NULL, del);
		i++;
	}
	pth[i] = NULL;
	i = 0;
	while (pth[i])
	{
		chdir(pth[i]);
		if (stat(com, &buff) == 0)
		{
			pth[i] = _strncat(pth[i], &ch, 1);
			com = _strcat(pth[i], com);
			break;
		}
		i++;
	}
	chdir(cwd);
	return (com);
}

/**
 * strncat - concatenate two strings
 * @str1: first string
 * @str2: other string
 * @n: length
 * Return: concatenated string
 */
char *_strncat(char *str1, char *str2, int n)
{
	int i, m = _strlen(str1);

	for (i = 0; i < n && str2[i] != '\0'; i++)
	{
		str1[m + i] = str2[i];
	}
	str1[m + i] = '\0';
	return (str1);
}

/**
 * _strcat - concatenate two strings
 * @dest: destination
 * @src: source string
 * Return: concatenated string
 */
char *_strcat(char *str1, char *str2)
{
	char *start = str1;

	while (*str1 != '\0')
		str1++;
	while (*str2 != '\0')
	{
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = '\0';
	return (start);
}
