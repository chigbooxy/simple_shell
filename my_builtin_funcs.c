#include "shell.h"
/**
 * my_myexit - exits the shell completly
 * @inf: Structure containing arguments.
 * Return: always an integer
 */

int my_myexit(info_t *inf);
int my_myexit(info_t *inf)
{
	int exit;

	if (inf->my_argv[1])
	{
		exit = my_erratoi(inf->my_argv[1]);
		if (exit == -1)
		{
			inf->my_status = 2;
			my_printerror(inf, "unacceptable number: ");
			my_eputs(inf->my_argv[1]);
			my_eputchar('\n');
			return (1);
		}
		else
		{
			inf->my_errnum = my_erratoi(inf->my_argv[1]);
			return (-2);
		}
	}
	inf->my_errnum = -1;
	return (-2);
}
/**
 * my_mycd - changes the current directory of the process
 * @inf: Structure containing arguments
 * Return: Always an integer
 */
int my_mycd(info_t *inf)
{
	char *si, *diir, buffer[1024];
	int chdirret;

	si = getcwd(buffer, 1024);
	if (!si)
		my_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->my_argv[1])
	{
		diir = my_getenv(inf, "HOME=");
		if (!diir)
			chdirret = chdir((diir = my_getenv(inf, "PWD=")) ? diir : "/");
		else
			chdirret = chdir(diir);
	}
	else if (my_strcmp(inf->my_argv[1], "-") == 0)
	{
		if (!my_getenv(inf, "OLDPWD="))
		{
			my_puts(si);
			my_putchar('\n');
			return (1);
		}
		my_puts(my_getenv(inf, "OLDPWD=")), my_putchar('\n');
		chdirret = chdir((diir = my_getenv(inf, "OLDPWD=")) ? diir : "/");
	}
	else
		chdirret = chdir(inf->my_argv[1]);
	if (chdirret == -1)
	{
		my_printerror(inf, "can't cd to ");
		my_eputs(inf->my_argv[1]), my_eputchar('\n');
	}
	else
	{
		my_setenv(inf, "OLDPWD", my_getenv(inf, "PWD="));
		my_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * my_myhelp - helper func
 * @inf: containins arguments
 * Return: Always an integer
 */
int my_myhelp(info_t *inf)
{
	char **my_argarray;

	my_argarray = inf->my_argv;
	my_puts("Help function is not yet implemented.\n");

	if (0)
		my_puts(*my_argarray);

	return (0);
}
