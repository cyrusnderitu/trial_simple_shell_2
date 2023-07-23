#include "shell.h"

/**
 * _strcat - Concatenates two strings
 *  @dest: The string to be appended upon.
 *  @src: The string to be appended to dest.
 *  Return: A pointer to the resulting string dest.
 *
 */
char *_strcat(char *dest, char *src)
{
	int index = 0, dest_len = 0;

	while (dest[index++])
		dest_len++;
	for (index = 0; src[index]; index++)
		dest[dest_len++] = src[index];
	return (dest);
}

/**
 * _strcpy - copies the string pointed to by src
 * @dest: pointer to the destiination address
 * @src: pointer to the string
 * Return: destination to pointer
 */

char *_strcpy(char *dest, char *src)
{
	char *dest_ptr = dest;

	if (dest == NULL)
		return (NULL);
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_ptr);
}

/**
 * _strcmp - Compares pointers to two strings.
 * @s1: A pointer to the first string to be compared.
 * @s2: A pointer to the second string to be compared.
 * Return: Comparison betw
 * If str1 < str2, the negative difference of the first unmatched characters.
 * If str1 == str2, 0.
 * If str1 > str2, the positive difference of the first unmatched characters.
 */
int _strcmp(char *s1, char *s2)
{
while ((*s1 && *s2) && (*s1 == *s2))
{
s1++;
s2++;
}
return (*s1 - *s2);
}

/**
 *collect_args - collects input from user
 *Return: pointer to array
 */
char *collect_args(void)
{
	size_t len = 0;
	char *ptr = NULL, *line = NULL;
	ssize_t nread;

	write(STDOUT_FILENO, "#cisfun$ ", 9);
	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		ptr = malloc(nread + 1);
		_strcpy(ptr, line);
		free(line);
		break;
	}
	if (nread == -1)
	{
		write(1, "\n", 1);
		exit(0);
	}
	return (ptr);
}

/**
 * breakdown - tokenizes the user input and parses it for evaluation
 * @ptr: pointer to the user input string for tokenizing
 */

void breakdown(char *ptr)
{
	pid_t child;
	struct stat st;
	char delim[] = " \n", *arr[1024], PATH[100] = "/bin/";
	char *portion = strtok(ptr, delim);
	int i = 0;

	if (portion == NULL)
	{
		free(ptr);
		exit(0);
	}
	while (portion != NULL)
	{
		arr[i] = portion;
		i++;
		portion = strtok(NULL, delim);
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
				free(ptr);
				break;
			}
		}
	if (child == 0 && (execve(arr[0], arr, NULL) == -1))
		perror("Could not execute");
}
