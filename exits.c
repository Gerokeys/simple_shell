#include "shell.h"

/**erty
 **_strncpy - copies a stringert
 *@dest: the destination striertyng to be copied to
 *@src: the source stringrtye
 *@n: tdgfhdgfhe amount of charactsfdsers to be copied
 *Return: the hjkfconcatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first stringada
 *@src: the second stringadad
 *@n: the amount of bytes to asgasgbe maximally used
 *Return: the concatenated stringasgadaae
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character inastring
 *@s: the string to be parsed
 *@c: the character to look forzdsfaga
 *Return: (s) a pointer to the memorday area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

