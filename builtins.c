#include "shell.h"

/**
 * print_env - Prints the current environment variables
 *
 * Description: Loops through the environ array and prints
 * each variable followed by a newline.
 */
void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * handle_builtin - Checks and executes built-in commands
 * @args: Array of command arguments
 *
 * Description: Handles "exit" and "env" built-in commands.
 *
 * Return: 1 if a built-in was handled, 0 otherwise,
 * 2 if the command is exit (signal to stop the shell)
 */
int handle_builtin(char **args)
{
	if (args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
		return (2);

	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}
