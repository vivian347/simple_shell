#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;
char *name;
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * @brief 
 * 
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **start);
} builtin_t;
/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

alias_t *aliases;

int alias_shell(char **args, char __attribute__((__unused__)) **start);
void alias_prt(alias_t *alias);
char **alias_rep(char **args);
void al_set(char *name, char *val);
int exit_fn(char **args, char **start);
int help(char **args, char __attribute__((__unused__)) **start);
int cd(char **args, char __attribute__((__unused__)) **start);
int (*getcmd_builtin(char *cmd))(char **args, char **start);
int get_len(const char *s);
char *cpy_str(char *str1, const char *str2);
char *cat_str(char *str1, const char *str2);
char *ncat_str(char *str1, const char *str2, size_t n);
char *strchr_fnc(char *s, char c);
int initlen_sub(char *s, char *acc);
int cmp(char *str1, char *str2);
int ncmp(const char *str1, const char *str2, size_t n);
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
char *get_val(char *env, int len);
void free_args(char **args, char **start);
char *_pid(void);
void rep_var(char **args, int *ret);
char *e_env(char **arg);
char *e_1(char **arg);
char *e_2_exit(char **arg);
char *e_2_cd(char **arg);
char *e_2_syntax(char **arg);
char *e_126(char **arg);
char *e_127(char **arg);
int dig_len(int n);
char *itoa_fnc(int n);
int create_err(char **arg, int error);
void *_realloc(void *p, unsigned int o_size, unsigned int n_size);
void _lineptr(char **lineptr, size_t *n, char *buf, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t new_len(char *arg);
void log_oper(char *ptr, ssize_t *ptr_new);
void split_line(char **ptr, ssize_t len);
int *fetch_cmd(char *buff, int *ret);
int cmd_handler(int *ret);
int exec_cmd(char **args, char **start, int *ret);
int check_cmd(char **args);
int arg_call(char **args, char **start, int *ret);
char **strtok_fnc(char *str, char *del);
int len_tok(char *str, char *del);
int tok_count(char *str, char *del);
void free_list(list_t *ptr);
void aliaslist_free(alias_t *ptr);
list_t *endnode_add(list_t **head, char *dir);
alias_t *endalias_add(alias_t **head, char *identifier, char *val);
char *_loc(char *cmd);
char *fill_path(char *path);
list_t *get_path(char *path);
void _signal(int sig);
int _exec(char **arg, char **start);
int cant_open(char *_path);
int proc_cmd(char *_path, int *exe_ret);



#endif
