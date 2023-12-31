#include "shell.h"

/**
 * finalizer - tokenizes the user input and parses it for evaluation
 * @ptr: pointer to the user input string for tokenizing
 */
void finalizer(char *ptr)
{
	struct stat st;
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
	
	switch (stat(arr[0], &st))
    {
        case 0:
        {
            child = fork();
            break;
        }
        default:
        {
            if (_strcmp(arr[0], "exit") == 0)
            {
                kill(getpid(), SIGINT);
            }
            _strcat(PATH, arr[0]);
            if (stat(PATH, &st) != 0)
                perror("could not find file");
            else
            {
                arr[0] = PATH;
                child = fork();
            }
            break;
        }
    	if (child == 0 && (execve(arr[0], arr, NULL) == -1))
        	perror("Could not execute");
	}
}
