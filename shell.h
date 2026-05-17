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
int execute(char *command, char *program_name);

#endif /* SHELL_H */
