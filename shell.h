#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int cmp(char *str1, char *str2);
char **parse(char *buffer, char *del);
char *concat(char *s1, char *s2);

#endif
