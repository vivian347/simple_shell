#include "shell.h"

/**
 * _parse - tokenize string
 * @buff: string to be tokenized
 *
 * Return: pointer to tokenized  str
 */

char **_parse(char *buff)
{
    char *token, **str;
    const char *delim = " ";
    int i;

    str = malloc(sizeof(char *) * MAX_SIZE);
    if (str == NULL)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    token = strtok(buff, delim);
    i = 0;
    while (token)
    {
        str[i] = token;
        token = strtok(NULL, delim);
        i++;
    }
    str[i] = NULL;
    return (str);
}