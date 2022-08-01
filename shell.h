#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
extern char **environ;

#define MAX_SIZE 1024

char *
_strdup(const char *s);
void *_realloc(void *ptr, size_t n);
int _strcmp(const char *str1, const char *str2);
char **_parse(char *buff);
// void print_env(void);

#endif