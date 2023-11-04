#include "shell.h"
/**
 * my_bfree - frees a pointer and sets the address to NULL;
 * @pointer: address of the pointer to be freed
 * Return: always an integer
 */

int my_bfree(void **pointer)
{
	int my_freed = 0;

	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}

	return (my_freed);
}

