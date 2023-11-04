#include "shell.h"
/**
 * my_myhistory - displays the history list
 * @inf: Structure contains arguments.
 *  Return: Always an integer
 */
int my_myhistory(info_t *inf)
{
	my_printlist(inf->my_history);
	return (0);
}
/**
 * my_unsetalias - removes alias to a string
 * @inf: parameter
 * @string: the string alias
 * Return: Always an integer
 */
int my_unsetalias(info_t *inf, char *string)
{
	char *my_pointer, c;
	int my_result;

	my_pointer = my_strchr(string, '=');
	if (!my_pointer)
		return (1);
	c = *my_pointer;
	*my_pointer = 0;
	my_result = my_delete(&(inf->my_alias),
	my_getnodeindex(inf->my_alias, my_nodestartswith(inf->my_alias, string, -1)));
	*my_pointer = c;
	return (my_result);
}
/**
 * my_setalias - sets alias to string
 * @inf: parameter
 * @string: the string alias
 * Return: Always an integer
 */

int my_setalias(info_t *inf, char *string)
{
	char *my_pointer;

	my_pointer = my_strchr(string, '=');
	if (!my_pointer)
		return (1);
	if (!*++my_pointer)
		return (my_unsetalias(inf, string));

	my_unsetalias(inf, string);
	return (my_addnodeend(&(inf->my_alias), string, 0) == NULL);
}
/**
 * my_printalias - prints an alias string to stdout
 * @noders: the alias node
 * Return: Always an integer
 */
int my_printalias(list_t *noders)
{
	char *point, *b;

	if (noders)
	{
		point = my_strchr(noders->string, '=');
		for (b = noders->string; b <= point; b++)
			my_putchar(*b);
		my_putchar('\'');
		my_puts(point + 1);
		my_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * my_myalias - creates an alias
 * @inf: Structure containing potential arguments
 *  Return: Always an integer
 */
int my_myalias(info_t *inf)
{
	int a = 1;
	char *point = NULL;

	if (inf->my_argc == 1)
	{
		list_t *noder = inf->my_alias;

		while (noder)
		{
			my_printalias(noder);
			noder = noder->nexts;
		}
		return (0);
	}

	while (inf->my_argv[a])
	{
		point = my_strchr(inf->my_argv[a], '=');

		if (point)
		{
			my_setalias(inf, inf->my_argv[a]);
		}
		else
		{
			list_t *my_alias_noder;

			my_alias_noder = my_nodestartswith(inf->my_alias, inf->my_argv[a], '=');

			if (my_alias_noder)
			{
				my_printalias(my_alias_noder);
			}
		}
		a++;
	}

	return (0);
}
