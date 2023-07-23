#include "shell.h"

/**
 * _execute - creates child process and run execve
 * @ptr: pointer to the user input string for tokenizing
 */
void _execute(char *ptr)
{
	pid_t child;
	char *arr[1024];
	char *token;
	int i = 0;

	token = _strtok(ptr, " ");
	if (token == NULL)
	{
    		free(ptr);
		exit(0);
	}
	while (portion != NULL)
	{
		arr[i] = token;
		i++;
		token = _strtok(NULL, delim);
	}
	if (_strcmp(arr[0], "exit") == 0)
	{
		kill(getpid(), SIGINT);
	}
	else
	{
		child = fork();
	}
	break;	
	if (child == 0 && (execve(arr[0], arr, NULL) == -1))
		perror("Could not execute");
}
