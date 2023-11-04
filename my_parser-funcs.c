#include "shell.h"
/**
 * my_iscmd - entry
 * @inf: info
 * @mypath: my path
 * Return: 0 or 1
 */
int my_iscmd(info_t *inf, char *mypath)
{
	struct stat stats;

	(void)inf;

	if (!mypath || stat(mypath, &stats))
		return (0);

	if (stats.st_mode & __S_IFREG)
		return (1);
	return (0);
}
/**
 * my_dupchars - entry
 * @mypathstring: path strings
 * @mystart: strings start
 * @mystop: my stop
 * Return: buffer
 */
char *my_dupchars(char *mypathstring, int mystart, int mystop)
{
	static char buffer[1024];
	int in = mystart, ki = 0;

	while (in < mystop)
	{
		if (mypathstring[in] != ':')
		{
			buffer[ki++] = mypathstring[in];
		}
		in++;
	}
	buffer[ki] = 0;
	return (buffer);
}
/**
 * my_findpath - entry
 * @myinfo: infomate
 * @mypathstr: path
 * @mycmd: command
 * Return: NULL
 */
char *my_findpath(info_t *myinfo, char *mypathstr, char *mycmd)
{
	int a = 0;
	int my_currpos = 0;
	char *mypath = NULL;

	if (!mypathstr)
		return (NULL);
	if ((my_strlen(mycmd) > 2) && my_startswith(mycmd, "./"))
	{
		if (my_iscmd(myinfo, mycmd))
			return (mycmd);
	}

	while (1)
	{
		if (!mypathstr[a] || mypathstr[a] == ':')
		{
			mypath = my_dupchars(mypathstr, my_currpos, a);
			if (!*mypath)
				my_strcat(mypath, mycmd);
			else
			{
				my_strcat(mypath, "/");
				my_strcat(mypath, mycmd);
			}
			if (my_iscmd(myinfo, mypath))
				return (mypath);
			if (!mypathstr[a])
				break;
			my_currpos = a;
		}
		a++;
	}
	return (NULL);
}

