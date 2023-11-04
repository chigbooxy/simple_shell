#include "shell.h"
/**
 * my_ischain - entry
 * @buffs: buffers
 * @pin: pins
 * @infos: info
 * Return: 1 or 0
 */
int my_ischain(info_t *infos, char *buffs, size_t *pin)
{
	size_t a = *pin;

	if (buffs[a] == '|' && buffs[a + 1] == '|')
	{
		buffs[a] = 0;
		a++;
		infos->cmdtype = MYCMDOR;
	}
	else if (buffs[a] == '&' && buffs[a + 1] == '&')
	{
		buffs[a] = 0;
		a++;
		infos->cmdtype = MYCMDAND;
	}
	else if (buffs[a] == ';')
	{
		buffs[a] = 0;
		infos->cmdtype = MYCMDCHAIN;
	}
	else
		return (0);
	*pin = a;
	return (1);
}
/**
 * my_checkchain - entry
 * @inf: info
 * @bfs: buffers
 * @pin: pin
 * @in: integer
 * @l: lengths
 */
void my_checkchain(info_t *inf, char *bfs, size_t *pin, size_t in, size_t l)
{
	size_t a = *pin;

	if (inf->cmdtype == MYCMDAND)
	{
		if (inf->my_status)
		{
			bfs[in] = 0;
			a = l;
		}
	}
	if (inf->cmdtype == MYCMDOR)
	{
		if (!inf->my_status)
		{
			bfs[in] = 0;
			a = l;
		}
	}

	*pin = a;
}
/**
 * my_replacealias - entry
 * @inf: inner info
 * Return: 1 or 0
 */
int my_replacealias(info_t *inf)
{
	int in;
	list_t *noder;
	char *pin;

	for (in = 0; in < 10; in++)
	{
		noder = my_nodestartswith(inf->my_alias, inf->my_argv[0], '=');
		if (!noder)
			return (0);
		free(inf->my_argv[0]);
		pin = my_strchr(noder->string, '=');
		if (!pin)
			return (0);
		pin = my_strdup(pin + 1);
		if (!pin)
			return (0);
		inf->my_argv[0] = pin;
	}
	return (1);
}
/**
 * my_replacevars - entry
 * @infos: informa
 * Return: 1 or 0
 */
int my_replacevars(info_t *infos)
{
	int in = 0;
	list_t *noder;

	for (in = 0; infos->my_argv[in]; in++)
	{
		if (infos->my_argv[in][0] != '$' || !infos->my_argv[in][1])
			continue;

		if (!my_strcmp(infos->my_argv[in], "$?"))
		{
			my_replacestring(&(infos->my_argv[in]),
							 my_strdup(my_convertnumber(infos->my_status, 10, 0)));
			continue;
		}
		if (!my_strcmp(infos->my_argv[in], "$$"))
		{
			my_replacestring(&(infos->my_argv[in]),
							 my_strdup(my_convertnumber(getpid(), 10, 0)));
			continue;
		}
		noder = my_nodestartswith(infos->my_env, &infos->my_argv[in][1], '=');
		if (noder)
		{
			my_replacestring(&(infos->my_argv[in]),
							 my_strdup(my_strchr(noder->string, '=') + 1));
			continue;
		}
		my_replacestring(&infos->my_argv[in], my_strdup(""));
	}
	return (0);
}
/**
 * my_replacestring - entry
 * @older: string old
 * @newer: strings new
 * Return: 0 and 1
 */
int my_replacestring(char **older, char *newer)
{
	free(*older);
	*older = newer;
	return (1);
}
