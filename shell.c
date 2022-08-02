#include "shell.h"

/**
 * main - Entry point
 * @argc: argument counter
 * @argv: argumnet Vector
 * @envp: environment pointer
 *
 * Return: 0
 */

int main(int __attribute__((unused)) argc, char **argv,
         char *envp[])
{
    char *buff = malloc(MAX_SIZE);
    size_t len = MAX_SIZE;
    pid_t pid;
    int i;

    while (1)
    {
        if (isatty(STDIN_FILENO) == 1)
        {
            printf("$ ");
        }
        if (getline(&buff, &len, stdin) == -1)
        {
            perror("Error");
            break;
        }

        argv = _parse(buff);

        if (argv == NULL)
        {
            free(argv);
            return (1);
        }

        pid = fork();

        if (pid == -1)
        {
            perror("Error");
            return (1);
        }
        if (pid == 0)
        {
            if (_strcmp(argv[0], "env") == 0)
            {
                for (i = 0; environ[i]; i++)
                {
                    printf("%s\n", environ[i]);
                }
                free(argv);
                continue;
            }
	    if (_strchr(argv[0], '/') == NULL)
	    {
		    argv[0] = _path(argv[0]);
	    }
            if (execve(argv[0], argv, envp) == -1)
            {
                perror("Error");
                exit(EXIT_FAILURE);
                return (-1);
            }
        }
        else
        {
            wait(NULL);
            free(argv);
        }
    }
    free(buff);
    return (0);
}
