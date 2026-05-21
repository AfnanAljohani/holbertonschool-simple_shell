#include "shell.h"

/**
 * execute - Forks and executes a command using PATH
 * @args: NULL-terminated array of arguments
 * @program_name: argv[0] of the shell, for error messages
 *
 * Description: Searches for the command in PATH using find_path,
 * then forks and uses execve to run it. The parent waits for
 * the child to finish.
 *
 * Return: 0 on success, 1 on error
 */
int execute(char **args, char *program_name)
{
	pid_t pid;
	int status;
	char *full_path;

	full_path = find_path(args[0]);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n",
			program_name, args[0]);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(program_name);
		free(full_path);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror(program_name);
			free(full_path);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(full_path);
	}
	return (0);
}
