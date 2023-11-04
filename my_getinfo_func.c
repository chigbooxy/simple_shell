#include "shell.h"
/**
 * my_clearinfo - will initialize the info_t struct
 * @inf: contains struct address
 */
void my_clearinfo(info_t *inf)
{
	inf->argsm = NULL;
	inf->my_argv = NULL;
	inf->my_path = NULL;
	inf->my_argc = 0;
}
/**
 * my_setinfo - will initialize the info_t struct
 * @inf: the struct address
 * @avs: argument vector
 */
void my_setinfo(info_t *inf, char **avs)
{
	int a = 0;

	inf->my_f_name = avs[0];
	if (inf->argsm)
	{
		inf->my_argv = mystrtow(inf->argsm, " \t");
		if (!inf->my_argv)
		{
			inf->my_argv = malloc(sizeof(char *) * 2);
			if (inf->my_argv)
			{
				inf->my_argv[0] = my_strdup(inf->argsm);
				inf->my_argv[1] = NULL;
			}
		}

		while (inf->my_argv && inf->my_argv[a])
		{
			a++;
		}
		inf->my_argc = a;

		my_replacealias(inf);
		my_replacevars(inf);
	}
}
/**
 * my_freeinfo - frees info_t struct
 * @inf: struct address
 * @al: true if all fields freed
 */
void my_freeinfo(info_t *inf, int al)
{
	my_ffree(inf->my_argv);
	inf->my_argv = NULL;
	inf->my_path = NULL;

	if (al)
	{
		if (!inf->mycmduf)
			free(inf->argsm);
		if (inf->my_env)
			my_freelist(&(inf->my_env));
		if (inf->my_history)
			my_freelist(&(inf->my_history));
		if (inf->my_alias)
			my_freelist(&(inf->my_alias));
		my_ffree(inf->my_envir);
		inf->my_envir = NULL;
		my_bfree((void **)inf->mycmduf);
		if (inf->reader > 2)
			close(inf->reader);
		my_putchar(MYBUFLUSH);
	}
}
