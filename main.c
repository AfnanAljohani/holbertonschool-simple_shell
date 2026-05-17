#include "shell.h"

/**
 * prompt - Displays the shell prompt
 *
 * Description: Prints "#cisfun$ " only in interactive mode
 * (when stdin is connected to a terminal).
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		printf("#cisfun$ ");
	fflush(stdout);
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
 * main - Entry point for the simple shell
 * @argc: Argument count (unused)
 * @argv: Argument vector, argv[0] used for error messages
 *
 * Description: Main shell loop. Displays prompt, reads a
 * command, executes it. Continues until EOF (Ctrl+D).
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;

	(void)argc;
	while (1)
	{
		prompt();
		line = read_line();
		if (line == NULL)
			break;
		if (line[0] != '\0')
			execute(line, argv[0]);
		free(line);
	}
	return (0);
}
