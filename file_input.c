#include "shell.h"

/**
 * run_file - read and execute commands from a file
 * @filename: path to script file
 * @program_name: argv[0]
 * Return: exit status
 */
int run_file(const char *filename, char *program_name)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	fp = fopen(filename, "r");
	if (!fp)
	{
		fprintf(stderr, "%s: 0: Can't open %s\n", program_name, filename);
		return (127);
	}
	while ((nread = getline(&line, &len, fp)) != -1)
	{
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		strip_comment(line);
		if (line[0] == '\0')
			continue;
		add_history(line);
		run_line(line, program_name);
	}
	free(line);
	fclose(fp);
	return (g_last_status);
}
