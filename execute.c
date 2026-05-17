#include "shell.h"

/**
 * execute - Forks and executes a command
 * @command: The full path command to execute
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
int execute(char *command, char *program_name)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

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
				program_name, command);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}
