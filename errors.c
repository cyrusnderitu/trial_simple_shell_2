#include "shell.h"

/**
 * print_error - prints the error message to the standard error
 * @msg: error message to print
 */
void print_error(char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
}
