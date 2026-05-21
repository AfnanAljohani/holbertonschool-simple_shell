#include "shell.h"

/**
 * execute - Forks and executes a command with arguments
 * @args: NULL-terminated array of arguments (args[0] = command)
 * @program_name: argv[0] of the shell, for error messages
 *
 * Description: Creates a child process. The child calls
 * execve to run the command. The parent waits for the child
 * to finish. If execve fails, prints an error in the format
 * "program_name: 1: command: not found" to stderr, matching
 * sh behavior.
 *
 * Return: 0 on success, 1 on fork failure
 */
int execute(char **args, char *program_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(program_name);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n",
				program_name, args[0]);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}
