#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int alias_shell(char **args, char _attribute((unused_)) **start);
void alias_prt(alias_t *alias);
char *alias_rep(char **args);
void al_set(char *name, char *val);
int _exit(char **args, char **start);
int help(char **args, char __attribute((unused_)) **start);
int cd(char **args, char __attribute((unused_)) **start);
int (*getcmd_builtin(char *cmd))(char **args, char **start);
int get_len(const char *s);
char *cpy_str(char *str1, const char *str2);
char *cat_str(char *str1, const char *str2);
char *ncat_str(char *str1, const char *str1, size_t n);
char *strchr_fnc(char *s, char c);
int initlen_sub(char *s, char *acc);
int cmp(char *str1, char *str2);
int ncmp(const char *str1, const char *str2m size_t n);
void h_all(void);
void h_alias(void);
void h_cd(void);
void h_exit(void);
void h_help(void);
void h_env(void);
void h_setenv(void);
void h_unsetenv(void);
int _env(char **args, char __attribute__((__unused__)) **start);
int _setenv(char **args, char __attribute__((__unused__)) **start);
int _unsetenv(char **args, char __attribute__((__unused__)) **start);
char **getenv_fnc(const char *env_var);
char **env_cpy(void);
void free_env(void);


#endif
