#include "shell.h"

int main(int __attribute__((unused))argc, char **argv, char **envp)
{
    char *buffer, *path, *str, **pth;
    size_t buffersize = 32;
    /*size_t chr;*/
    int cmpres, i; /*cmpempt,*/
    pid_t pid;
    char del[] = ":";
    char *buff, *buff1;
    char *ch = "/";

    while (1)
    {
        /*===read input from user===*/
        /*allocate memory*/
        buff = (char *)malloc(buffersize * sizeof(char));
        buff1 = (char *)malloc(buffersize * sizeof(char));
        buffer = (char *)malloc(buffersize * sizeof(char));
        /*on fail allocation of memory*/
        if (buffer == NULL)
        {
            perror("Unable to allocate buffer!");
            exit(1);
        }
        printf("$: ");
        getline(&buffer, &buffersize, stdin);/*chr is used here*/

        /*if user wants to exit*/
        cmpres = cmp("exit", buffer);
        if (cmpres == 0)
        {
            printf("exiting shell...\n");
            break;
        }
        /*if cmd is empty*/
        /*cmpempt = cmp("", buffer);
        if(cmpempt == 0)
        {
            perror("Empty input.Enter command!\n");
            continue;
        }*/

        /*parse cmd into argv  */
        argv = parse(buffer, " ");
        
        /*fork parent*/
        pid = fork();

        if (pid == -1)
        {
            perror("Could not fork!");
            exit(1);
        }
        if (pid == 0)
        {
            if (strchr(argv[0], '/') == NULL)
            {
                path = getenv("PATH");
            pth = malloc(sizeof(char *) * 1024);

            if (pth == NULL)
            {
                perror("No argv memory allocated");
                exit(1);
            }
            str = strtok(path, del);
            /*get remaining tokens in buffer and store in argv[]*/
            i = 0;
            while (str != NULL)
            {
                pth[i] = str;
                /*printf("argv[%d] %s\n", i, pth[i]);*/
                i++;
                str = strtok(NULL, del);
            }
            pth[i] = NULL;
            buff1 = concat(pth[i], ch);
            buff = concat(buff1, argv[0]);
            
            if (access(buff, X_OK) == -1)
            {
                perror("access!X");
                exit(EXIT_FAILURE);
                
            }
            }
            
            if (execve(buff, argv, envp))
            {
                perror("Execution failure!");
                exit(EXIT_FAILURE);
                break;
            }
            
            

        }
        wait(NULL);
        free(argv);
        
        /*display environment variables*/
        /*while (*envp != NULL)
            printf("%s\n", *(envp++));*/
        
    }
    return (0);
}