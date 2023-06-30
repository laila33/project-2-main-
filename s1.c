#include "shell_.h"

int strlen_func(const char *ptr);
char *strcpy_func(char *s2, const char *s1);
char *strcat_func(char *s2, const char *s1);
char *strncat_func(char *s2, const char *s1, size_t am);

/**
 * strlen_func - Return length of string.
 * @ptr: Pointer to char string.
 *
 * Return: size of the character string.
 */
int strlen_func(const char *ptr)
{
	int j = 0;

	if (!ptr)
		return (j);
	for (j = 0; ptr[j]; j++)
		;
	return (j);
}

/**
 * strcpy_func - copy string pointed to by s1.
 * @s2: Pointer to the destination of copied string.
 * @s1: Pointer to the source string.
 *
 * Return: pointer to s2.
 */
char *strcpy_func(char *s2, const char *s1)
{
	size_t j;

	for (j = 0; s1[j] != '\0'; j++)
		s2[j] = s1[j];
	s2[j] = '\0';
	return (s2);
}

/**
 * strcat_func - Concantenate two String
 * @s2: pointer to s2 string.
 * @s1: Pointer to source string.
 *
 * Return: pointer to s2.
 */
char *strcat_func(char *s2, const char *s1)
{
	char *s22;
	const char *s11;

	s22 = s2;
	s11 =  s1;

	while (*s22 != '\0')
		s22++;

	while (*s11 != '\0')
		*s22++ = *s11++;
	*s22 = '\0';
	return (s2);
}

/**
 * strncat_func - concantenate two string.
 * @s2: Pointer to THE destination string.
 * @s1: Pointer to THE source string.
 * @am: bytes to copy from s1.
 *
 * Return: pointer to destination string.
 */
char *strncat_func(char *s2, const char *s1, size_t am)
{
	size_t s2_len = strlen_func(s2);
	size_t j;

	for (j = 0; j < am && s1[j] != '\0'; j++)
		s2[s2_len + j] = s1[j];
	s2[s2_len + j] = '\0';

	return (s2);
}
