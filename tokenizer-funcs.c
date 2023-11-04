#include "shell.h"
/**
 * **mystrtow - splits a string into words.
 * @s: the input string
 * @dy: the delimeter
 * Return: a pointer to an array of strings
 */

char **mystrtow(char *s, char *dy);
char **mystrtow(char *s, char *dy)
{
	int in, jn, kn, mn, mynumwords = 0;
	char **sn;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!dy)
		dy = " ";
	for (in = 0; s[in] != '\0'; in++)
		if (!my_isdelimeter(s[in], dy) && (my_isdelimeter(s[in + 1], dy) ||
		!s[in + 1]))
			mynumwords++;

	if (mynumwords == 0)
		return (NULL);
	sn = malloc((1 + mynumwords) * sizeof(char *));
	if (!sn)
		return (NULL);
	for (in = 0, jn = 0; jn < mynumwords; jn++)
	{
		while (my_isdelimeter(s[in], dy))
			in++;
		kn = 0;
		while (!my_isdelimeter(s[in + kn], dy) && s[in + kn])
			kn++;
		sn[jn] = malloc((kn + 1) * sizeof(char));
		if (!sn[jn])
		{
			for (kn = 0; kn < jn; kn++)
				free(sn[kn]);
			free(sn);
			return (NULL);
		}
		for (mn = 0; mn < kn; mn++)
			sn[jn][mn] = s[in++];
		sn[jn][mn] = 0;
	}
	sn[jn] = NULL;
	return (sn);
}
/**
 * **mystrtow2 - splits a string into words
 * @stry: the input string
 * @dy: the delimeter
 * Return: a pointer to an array of strings
*/
char **mystrtow2(char *stry, char dy)
{
	int in, jn, kn, mn, mynumwords = 0;
	char **sn;

	if (stry == NULL || stry[0] == 0)
		return (NULL);
	for (in = 0; stry[in] != '\0'; in++)
		if ((stry[in] != dy && stry[in + 1] == dy) ||
			(stry[in] != dy && !stry[in + 1]) || stry[in + 1] == dy)
			mynumwords++;
	if (mynumwords == 0)
		return (NULL);
	sn = malloc((1 + mynumwords) * sizeof(char *));
	if (!sn)
		return (NULL);
	for (in = 0, jn = 0; jn < mynumwords; jn++)
	{
		while (stry[in] == dy && stry[in] != dy)
			in++;
		kn = 0;
		while (stry[in + kn] != dy && stry[in + kn] && stry[in + kn] != dy)
			kn++;
		sn[jn] = malloc((kn + 1) * sizeof(char));
		if (!sn[jn])
		{
			for (kn = 0; kn < jn; kn++)
				free(sn[kn]);
			free(sn);
			return (NULL);
		}
		for (mn = 0; mn < kn; mn++)
			sn[jn][mn] = stry[in++];
		sn[jn][mn] = 0;
	}
	sn[jn] = NULL;

	return (sn);
}
