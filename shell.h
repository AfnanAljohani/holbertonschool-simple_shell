#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args, char *program_name);
int handle_builtin(char **args);
void print_env(void);
char *find_path(char *command);
char *get_env(char *name);

#endif /* SHELL_H */
