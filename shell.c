#include "shell.h"
int main(int argc, char **argv)
{
	read_cmd();
	return (0);
}

void read_cmd(void)
{
	size_t buf_size = 15;
	ssize_t nread;
	char *buf = NULL;
	char *buf_cpy = NULL;
	printf("input command: ");
	nread = getline(&buf, &buf_size, stdin);

	if (nread == -1)
	{
		printf("\n....logging out\n");
		return;
	}
	buf_cpy = malloc(sizeof(char) * nread);
	strcpy(buf_cpy, buf);

	tokenizer(buf, buf_cpy);

	free(buf);
	free(buf_cpy);
}

void tokenizer(char *buf, char *buf_cpy)
{
	char *token;
	char delim[] = " \n";
	char **argv = NULL;
	int num_tok = 0, i;

	token = strtok(buf, delim);
	while (token)
	{
		num_tok++;
		token = strtok(NULL, delim);
	}
	num_tok++;
	argv = malloc(sizeof(char *) * num_tok);
	token = strtok(buf_cpy, delim);

	for (i = 0; token; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
		if (token == NULL)
		{
			i++;
			argv[i] = NULL;
		}
	}
	exec_cmd(argv);
	free(argv);
	free(token);
}

void exec_cmd(char **argv)
{
	pid_t pid;
	pid = fork();

	if (pid != 0)
	{
		wait(NULL);
		read_cmd();
	}
	else
	{
		if (execve(argv[0], argv, NULL) == -1)
			perror("input new command");
	}
}
