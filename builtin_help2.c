#include "shell.h"

void h_env(void);
void h_setenv(void);
void h_unsetenv(void);

/**
 * h_env - info on builtin command 'env'
 */

void h_env(void)
{
	char *msg = "en: env\n\tPrints the current environment";

	write(STDOUT_FILENO, msg, get_len(msg));
}

/**
 * h_setenv - info on builtin command 'setenv'
 */

void h_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, get_len(msg));
}

/**
 * h_unsetenv - info on builtin command 'unsetenv'
 */

void h_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, get_len(msg));
}
