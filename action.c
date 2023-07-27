#include "shell.h"

/**
 * action - executes the actual function
 * @ptr: ptr to item in list
*/
void action(char *ptr)
{
    struct stat st;

    switch (stat(ptr, &st))
    {
        case 0:
        {
            child = fork();
            break;
        }
        default:
        {
            if (_strcmp(ptr[0], "exit") == 0)
            {
                kill(getpid(), SIGINT);
            }
            else if (_strcmp(ptr[0], "cd") == 0)
            {
                if (ptr[1] != NULL && chdir(ptr[1]) == -1)
                {
                    perror("cd");
                }
                else
                    continue;
            _strcat(PATH, ptr[0]);
            if (stat(PATH, &st) != 0)
                perror("could not find file");
            else
            {
                ptr[0] = PATH;
                child = fork();
            }
            break;
            }
        }
    if (child == 0 && (execve(ptr[0], ptr, NULL) == -1))
        perror("Could not execute");
	}
}