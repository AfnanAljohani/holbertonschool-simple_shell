#include "shell.h"

/**
 * strip_comment - cut line at hash if it starts a comment
 * @line: input line modified in place
 */
void strip_comment(char *line)
{
	int i;

	if (!line)
		return;
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
		{
			if (i == 0 || line[i - 1] == ' ' || line[i - 1] == 9)
			{
				line[i] = '\0';
				return;
			}
		}
	}
}
