#include "shell_.h"

char *strchr_func(char *stt, char ch);
int strspn_func(char *stt, char *d);
int strcmp_func(char *stt1, char *stt2);
int strncmp_func(const char *stt1, const char *stt2, size_t am);

/**
 * strchr_func - find char in string.
 * @stt: The string to be searched.
 * @ch: The character to be located.
 *
 * Return:POINTER to the CHARACTER or NULL.
 */
char *strchr_func(char *stt, char ch)
{
	int i;

	for (i = 0; stt[i]; i++)
	{
		if (stt[i] == ch)
			return (stt + i);
	}

	return (NULL);
}

/**
 * strspn_func - find the length of a prefix Substring
 * @stt: string to be searched.
 * @d: The prefix Substring to measure.
 *
 * Return:Number of bytes.
 */
int strspn_func(char *stt, char *d)
{
	int n = 0;
	int i;

	while (*stt)
	{
		for (i = 0; d[i]; i++)
		{
			if (*stt == d[i])
			{
				n++;
				break;
			}
		}
		stt++;
	}
	return (n);
}

/**
 * strcmp_func - Comparee bitween strings.
 * @stt1: first string to compare.
 * @stt2: second string to compare.
 *
 * Return: Positive if stt1 > stt2
 *         0 if stt1 = stt2
 *         Negative if stt1 < stt2
 */

int strcmp_func(char *stt1, char *stt2)
{
	while (*stt1 && *stt2 && *stt1 == *stt2)
	{
		stt1++;
		stt2++;
	}

	if (*stt1 != *stt2)
		return (*stt1 - *stt2);

	return (0);
}

/**
 * strncmp_func - compare two strings.
 * @stt1: Pointer to first string.
 * @stt2: Pointer to second string.
 * @am: First number of bytes of the strings to compare.
 *
 * Return: Less than 0 if stt1 is shorter than stt2.
 *         0 if stt1 and stt2 match.
 *         Greater than 0 if stt1 is longer than stt2.
 */
int strncmp_func(const char *stt1, const char *stt2, size_t am)
{
	size_t j;

	for (j = 0; stt1[j] && stt2[j] && j < am; j++)
	{
		if (stt1[j] > stt2[j])
			return (stt1[j] - stt2[j]);
		else if (stt1[j] < stt2[j])
			return (stt1[j] - stt2[j]);
	}
	if (j == am)
		return (0);
	else
		return (-15);
}
