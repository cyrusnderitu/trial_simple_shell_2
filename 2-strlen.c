#include "shell.h"

/**
 *_strlen- calculates the length of a string
 *@s:string parameter to calculate the length
 *Return: Length of the string
 */

int _strlen(char *s)
{
	int countchar = 0;

	while (s[countchar] != '\0')
	{
		countchar++;
	}
	return (countchar);
}
