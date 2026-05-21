#include "shell.h"

/**
 * get_env - Gets the value of an environment variable
 * @name: The name of the variable (e.g., "PATH")
 *
 * Description: Searches the environ array for a variable.
 *
 * Return: Pointer to the value, or NULL if not found
 */
char *get_env(char *name)
{
	int i = 0;
	int len;

	if (name == NULL)
		return (NULL);
	len = strlen(name);
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * build_path - Builds a full path by joining directory and command
 * @dir: The directory
 * @command: The command name
 *
 * Description: Allocates memory for "dir/command" string.
 *
 * Return: Pointer to the full path, or NULL on failure
 */
char *build_path(char *dir, char *command)
{
	char *full_path;
	int len;

	len = strlen(dir) + strlen(command) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
		return (NULL);
	sprintf(full_path, "%s/%s", dir, command);
	return (full_path);
}

/**
 * find_path - Finds the full path of a command using PATH
 * @command: The command name (e.g., "ls")
 *
 * Description: If command contains '/', returns a copy of it.
 * Otherwise, searches each directory in PATH for the command.
 *
 * Return: Allocated string with full path, or NULL if not found
 */
char *find_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;

	if (command == NULL)
		return (NULL);
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	path = get_env("PATH");
	if (path == NULL || path[0] == '\0')
		return (NULL);
	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = build_path(dir, command);
		if (full_path != NULL && access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
