#include "shell.h"

void h_all(void);
void h_alias(void);
void h_cd(void);
void h_exit(void);
void h_help(void);

/**
 * h_all - display all builtin cmds
 */

void h_all(void)
{
	char *msg = "Shell\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "Type 'help' to see list.\nType 'help name to find.\n";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "out more abou 'name'.\n\n alias	\t";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "alias [NAME[='VALUE'] ...]\n cd	\tcd	";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "[DIRECTORY]\n exit	\texit [STATUS]\n env	\tenv";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "\n setenv \tsetenv [VARIABLE] [VALUE]\n	unsetenv\t";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, get_len(msg));
}

/**
 * h_alias - info on builtin command 'alias'
 */

void h_alias(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, get_len(msg));
}

/**
 * h_cd - info on builtin command 'cd'
 */

void h_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, get_len(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, get_len(msg));
}

/**
 * h_exit - info on builtin command 'exit'.
 */

void h_exit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, get_len(msg));
}

/**
 * h_help - info on builtin command 'help'
 */

void h_help(void)
{
	char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, get_len(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, get_len(msg));
}
