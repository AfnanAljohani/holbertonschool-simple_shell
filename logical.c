#include "shell.h"

/**
 * run_one_cmd - run a single command (no separators)
 * @segment: command text
 * @program_name: argv[0]
 * Return: exit status
 */
static int run_one_cmd(char *segment, char *program_name)
{
	char **args;
	int builtin_status, status = 0;

	segment = trim_spaces(segment);
	if (*segment == '\0')
		return (g_last_status);
	args = split_line(segment);
	if (!args || !args[0])
	{
		free(args);
		return (g_last_status);
	}
	builtin_status = handle_builtin(args);
	if (builtin_status == 2)
	{
		free(args);
		free_aliases();
		free_history();
		exit(g_last_status);
	}
	if (builtin_status == 0 && args[0] != NULL)
		status = execute(args, program_name);
	g_last_status = status;
	free(args);
	return (status);
}

/**
 * run_logical - run commands separated by && and ||
 * @segment: line segment
 * @program_name: argv[0]
 * Return: last exit status
 */
int run_logical(char *segment, char *program_name)
{
	char *p = segment, *start = segment;
	int status;

	while (*p)
	{
		if (p[0] == '&' && p[1] == '&')
		{
			*p = '\0';
			status = run_one_cmd(start, program_name);
			if (status != 0)
				return (status);
			p += 2;
			start = p;
		}
		else if (p[0] == '|' && p[1] == '|')
		{
			*p = '\0';
			status = run_one_cmd(start, program_name);
			if (status == 0)
				return (status);
			p += 2;
			start = p;
		}
		else
			p++;
	}
	return (run_one_cmd(start, program_name));
}

/**
 * run_line - run full line handling ; first, then && ||
 * @line: input line
 * @program_name: argv[0]
 * Return: last exit status
 */
int run_line(char *line, char *program_name)
{
	char **parts;
	int count = 0, i, status = 0;

	parts = split_by_str(line, ";", &count);
	if (!parts)
		return (g_last_status);
	for (i = 0; i < count; i++)
	{
		char *seg = trim_spaces(parts[i]);

		if (*seg != '\0')
			status = run_logical(seg, program_name);
	}
	for (i = 0; i < count; i++)
		free(parts[i]);
	free(parts);
	return (status);
}
