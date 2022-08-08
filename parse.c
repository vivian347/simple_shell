#include "shell.h"

char **parse(char *buffer, char *del)
{
    char *str, **argv = NULL;
    int i;
    argv = malloc(sizeof(char *) * 1024);

    if (argv == NULL)
    {
        perror("No argv memory allocated");
        exit(1);
    }
    str = strtok(buffer, del);
    /*get remaining tokens in buffer and store in argv[]*/
    i = 0;
    while (str != NULL)
    {
        argv[i] = str;
        printf("argv[%d] %s\n", i, argv[i]);
        i++;
        str = strtok(NULL, del);
    }
    argv[i] = NULL;
    return (argv);

}