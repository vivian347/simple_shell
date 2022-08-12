#include "shell.h"

void _signal(int sig);
int _exec(char **arg, char **start);

/**
 * _signal - prints new prompt upon a signal
 * @sig: signal
 *
 */

void _signal(int sig)
{
	char *_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, _signal);
	write(STDIN_FILENO, _prompt, 3);
}

/**
 * _exec - execute command in child process
 * @arg: arguments
 * @start: pointer to start of arg
 *
 * Return: exit val of last executed command
 */

int _exec(char **arg, char **start)
{
	pid_t pid;
	int stat, flag = 0, ret = 0;
	char *cmd = arg[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = _loc(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_err(arg, 126));
		else
			ret = (create_err(arg, 127));
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (pid == 0)
		{
			execve(cmd, arg, environ);
			if (errno == EACCES)
				ret = (create_err(arg, 126));
			free_env();
			free_args(arg, start);
			aliaslist_free(aliases);
			_exit(ret);
		}
		else
		{
			wait(&stat);
			ret = WEXITSTATUS(stat);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}
/**
 * main - entry point
 * @argc: argument counter
 * @argv: argument vector
 *
 * Return: return al of last executed command
 */

int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, _signal);

	*exe_ret = 0;
	environ = env_cpy();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		ret = proc_cmd(argv[1], exe_ret);
		free_env();
		aliaslist_free(aliases);
		return (*exe_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = cmd_handler(exe_ret);
		free_env();
		aliaslist_free(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = cmd_handler(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			aliaslist_free(aliases);
			exit(*exe_ret);
		}
	}
	free_env();
	aliaslist_free(aliases);
	return (*exe_ret);
}
