#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void read_cmd(void);
void tokenizer(char *buf, char *buf_cpy);
void exec_cmd(char **argv);
#endif
