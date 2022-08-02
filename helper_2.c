#include "shell.h"

unsigned int _strlen(const char *s);

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
