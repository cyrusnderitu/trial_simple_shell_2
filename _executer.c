#include "shell.h"

/**
 * finalizer - tokenizes the user input and parses it for evaluation
 * @ptr: pointer to the user input string for tokenizing
 */
void finalizer(char *ptr)
{
	pid_t child;
	char delim[] = " \n", *arr[1024], PATH[100] = "/bin/";
	int i = 0;
	char *token;

	token = strtok(ptr, delim);
	if (token == NULL)
	{
		free(ptr);
		exit(0);
	}
	while (token != NULL)
	{
		arr[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	action(arr);
	return (0);
}
