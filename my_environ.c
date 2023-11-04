#include "shell.h"
/**
 * my_myenv - entry
 * @inf: info
 * Return: 1 or 0
 */
int my_myenv(info_t *inf)
{
	my_printliststr(inf->my_env);
	return (0);
}
/**
 * my_getenv - entry
 * @inf: info
 * @nam: nam
 * Return: pointer
 */
char *my_getenv(info_t *inf, const char *nam)
{
	list_t *noder = inf->my_env;
	char *point;

	while (noder)
	{
		point = my_startswith(noder->string, nam);
		if (point && *point)
			return (point);
		noder = noder->nexts;
	}
	return (NULL);
}
/**
 * my_mysetenv - entry
 * @inf: info
 * Return: 1 or 0
 */
int my_mysetenv(info_t *inf)
{
	if (inf->my_argc != 3)
	{
		my_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (my_setenv(inf, inf->my_argv[1], inf->my_argv[2]))
		return (0);
	return (1);
}
/**
 * my_myunsetenv - entry
 * @inf: info
 * Return: 1 or 0
 */
int my_myunsetenv(info_t *inf)
{
	int a = 1;

	if (inf->my_argc == 1)
	{
		my_eputs("Too few arguments.\n");
		return (1);
	}

	for (; a <= inf->my_argc; a++)
		my_unsetenv(inf, inf->my_argv[a]);

	return (0);
}
/**
 * my_populateenvlist - entry
 * @inf: info
 * Return: 1 or 0
 */
int my_populateenvlist(info_t *inf)
{
	list_t *noder = NULL;
	size_t a = 0;

	for (; environ[a]; a++)
		my_addnodeend(&noder, environ[a], 0);

	inf->my_env = noder;
	return (0);
}
