#include "shell.h"

/**
 * prompt - Displays the shell prompt in interactive mode
 *
 * Description: Prints "#cisfun$ " only when stdin is a terminal.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}

/**
 * read_line - Reads one line of input from stdin
 *
 * Description: Uses getline to read a line. Strips the
 * trailing newline. Returns NULL on EOF (Ctrl+D).
 *
 * Return: Pointer to the line or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		if (isatty(STDIN_FILENO))
			printf("\n");
		return (NULL);
	}
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	return (line);
}

/**
 * split_line - Splits a line into tokens (arguments)
 * @line: The input line to split
 *
 * Description: Uses strtok to split by spaces and tabs.
 *
 * Return: Array of tokens, or NULL on failure
 */
char **split_line(char *line)
{
	char **tokens;
	char *token;
	int bufsize = 64, i = 0;

	tokens = malloc(sizeof(char *) * bufsize);
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, " \t");
	while (token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * main - Entry point for the simple shell
 * @argc: Argument count (unused)
 * @argv: Argument vector, argv[0] used for error messages
 *
 * Description: Main shell loop. Reads, parses, and executes
 * commands. Handles built-ins (exit, env) before forking.
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;
	char **args;
	int builtin_status;

	(void)argc;
	while (1)
	{
		prompt();
		line = read_line();
		if (line == NULL)
			break;
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		args = split_line(line);
		if (args == NULL)
		{
			free(line);
			continue;
		}
		builtin_status = handle_builtin(args);
		if (builtin_status == 2)
		{
			free(args);
			free(line);
			break;
		}
		if (builtin_status == 0 && args[0] != NULL)
			execute(args, argv[0]);
		free(args);
		free(line);
	}
	return (0);
}
