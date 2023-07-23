#include "shell.h"

/**
 * main - main file for computing all functions of shell
 * Return: 0 on success
 */
int main(void)
{
	char *command;
	char *token;
	char *argv1[100];
	int i = 0, j = 0;
	int status;
	pid_t child;

	if (isatty(fileno(stdin)))
	{
		while (1)
		{
			write(STDOUT_FILENO, "#cisfun$ ", 9);
			command = collect_args();
			if (command[_strlen(command) - 1] == '\n')
				command[_strlen(command) - 1] = '\0';
			if (_strcmp(command, "exit") == 0)
			{
				kill(getpid(), SIGINT);
			}
			token = _strtok(command, " ");
			while (token != NULL)
			{
				argv1[i] = token;
				i++;
				token = _strtok(NULL, " ");
			}
			argv1[i] = NULL;
			child = fork();
			if (child == 0)
			{
				execve(argv1[0], argv1, NULL);
				exit(1);
			}
			else if (child > 0)
			{
				wait(&status);
			}
			else
			{
				print_error("fork failed");
				exit(1);
			}
		}
	}
	else
	{
		while (fgets(command, sizeof(command), stdin) != NULL)
		{
			if (command[_strlen(command) - 1] == '\n')
				command[_strlen(command) - 1] = '\0';
			if (_strcmp(command, "exit") == 0)
				break;
			token = _strtok(command, " ");
			while (token != NULL)
			{
				argv1[j] = token;
				j++;
				token = _strtok(NULL, " ");
			}
			argv1[j] = NULL;
			child = fork();
			if (child == 0)
			{
				execve(argv1[0], argv1, NULL);
				fprintf(stderr, "./hsh: No such file or directory\n");
				exit(1);
			}
			else if (child > 0)
			{
				wait(&status);
			}
			else
			{
				print_error("fork failed");
				exit(1);
			}
		}
	}
	return (0);
}
