#include "shell.h"

/**
 * process_line - process a single input line
 * @line: input line
 * @program_name: argv[0]
 */
static void process_line(char *line, char *program_name)
{
	char *expanded, *aliased;

	strip_comment(line);
	while (*line == ' ' || *line == 9)
		line++;
	if (line[0] == '\0')
		return;
	add_history(line);
	expanded = expand_variables(line);
	if (!expanded)
		return;
	aliased = substitute_alias(expanded);
	free(expanded);
	if (!aliased)
		return;
	run_line(aliased, program_name);
	free(aliased);
}

/**
 * interactive_loop - run shell in interactive or piped mode
 * @program_name: argv[0]
 * Return: exit status
 */
static int interactive_loop(char *program_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int is_tty = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_tty)
		{
			printf("($) ");
			fflush(stdout);
		}
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (is_tty)
				printf("\n");
			break;
		}
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		process_line(line, program_name);
	}
	free(line);
	return (g_last_status);
}

/**
 * main - shell entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: last exit status
 */
int main(int argc, char **argv)
{
	int status;

	if (argc > 1)
	{
		status = run_file(argv[1], argv[0]);
	}
	else
	{
		status = interactive_loop(argv[0]);
	}
	free_aliases();
	free_history();
	return (status);
}
