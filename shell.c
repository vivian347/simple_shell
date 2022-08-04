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
    char *buff = NULL;
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
            perror("No line to print");
            break;
        }

        argv = _parse(buff);

        if (!argv[0])
        {
            free(argv);
            continue;
        }
        if (_strcmp(argv[0], "env") == 0)
        {
            for (i = 0; environ[i]; i++)
            {
                printf("%s\n", environ[i]);
            }
            free(argv);
            continue;
        }
        pid = fork();
        if (pid == -1)
        {
            perror("Error");
            return (1);
        }
        if (pid == 0)
        {
            if (_strchr(argv[0], '/') == NULL)
            {
                argv[0] = _path(argv[0]);
            }
            if (execve(argv[0], argv, envp))
            {
                perror("Error");
                exit(EXIT_FAILURE);
                break;
            }
        }
        wait(NULL);
        free(argv);
    }
    free(buff);
    return (0);
}
