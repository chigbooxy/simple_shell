#include "shell.h"
/**
 * my_hsh - entry point
 * @inf: info to the
 * @avs: character
 * Return: my_builtinret
 */

int my_hsh(info_t *inf, char **avs);
int my_hsh(info_t *inf, char **avs)
{
	ssize_t in = 0;
	int my_b = 0;

	while (in != -1 && my_b != -2)
	{
		my_clearinfo(inf);
		if (my_interactiveness(inf))
			my_puts("$ ");
		my_eputchar(MYBUFLUSH);
		in = my_getinput(inf);
		if (in != -1)
		{
			my_setinfo(inf, avs);
			my_b = my_findbuiltin(inf);
			if (my_b == -1)
				my_findcmd(inf);
		}
		else if (my_interactiveness(inf))
			my_putchar('\n');
		my_freeinfo(inf, 0);
	}
	my_writehistory(inf);
	my_freeinfo(inf, 1);
	if (!my_interactiveness(inf) && inf->my_status)
		exit(inf->my_status);
	if (my_b == -2)
	{
		if (inf->my_errnum == -1)
			exit(inf->my_status);
		exit(inf->my_errnum);
	}
	return (my_b);
}
/**
 * my_findbuiltin - entry point
 * @inf: info_t info
 * Return: 0 or 1
 */
int my_findbuiltin(info_t *inf);
int my_findbuiltin(info_t *inf)
{
	int in = 0;
	int myret = -1;
	mybuiltin_table mybuiltintbl[] = {
		{"exit", my_myexit},
		{"env", my_myenv},
		{"help", my_myhelp},
		{"history", my_myhistory},
		{"setenv", my_mysetenv},
		{"unsetenv", my_myunsetenv},
		{"cd", my_mycd},
		{"alias", my_myalias},
		{NULL, NULL}};

	while (mybuiltintbl[in].type)
	{
		if (my_strcmp(inf->my_argv[0], mybuiltintbl[in].type) == 0)
		{
			inf->my_linecount++;
			myret = mybuiltintbl[in].funct(inf);
			break;
		}
		in++;
	}

	return (myret);
}
/**
 * my_findcmd - finding command
 * @inf: info checker
 */
void my_findcmd(info_t *inf);
void my_findcmd(info_t *inf)
{
	char *pathers = NULL;
	int in = 0;
	int ki = 0;

	inf->my_path = inf->my_argv[0];
	if (inf->mylineflag == 1)
	{
		inf->my_linecount++;
		inf->mylineflag = 0;
	}
	for (in = 0, ki = 0; inf->argsm[in]; in++)
		if (!my_isdelimeter(inf->argsm[in], " \t\n"))
			ki++;
	if (!ki)
		return;

	pathers = my_findpath(inf, my_getenv(inf, "PATH="), inf->my_argv[0]);
	if (pathers)
	{
		inf->my_path = pathers;
		my_forkcmd(inf);
	}
	else
	{
		if ((my_interactiveness(inf) ||
			 my_getenv(inf, "PATH=") ||
			 inf->my_argv[0][0] == '/') &&
			my_iscmd(inf, inf->my_argv[0]))
			my_forkcmd(inf);
		else if (*(inf->argsm) != '\n')
		{
			inf->my_status = 127;
			my_printerror(inf, "not found\n");
		}
	}
}
/**
 * my_forkcmd - forking command
 * @inf: info at info_t
 */
void my_forkcmd(info_t *inf);
void my_forkcmd(info_t *inf)
{
	pid_t mychild_pid;

	mychild_pid = fork();
	if (mychild_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (mychild_pid == 0)
	{
		if (execve(inf->my_path, inf->my_argv, my_getenvironment(inf)) == -1)
		{
			my_freeinfo(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->my_status));
		if (WIFEXITED(inf->my_status))
		{
			inf->my_status = WEXITSTATUS(inf->my_status);
			if (inf->my_status == 126)
				my_printerror(inf, "Permission denied\n");
		}
	}
}

