/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marubio- <marubio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:46:17 by marubio-          #+#    #+#             */
/*   Updated: 2024/09/17 12:37:28 by marubio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * The function ft_strncmp() compares the first n characters of 
 * the strings s1 and s2
 * 
 * @param s1 The first string to be compared.
 * @param s2 The string to compare to.
 * @param n The maximum number of characters to compare.
 * 
 * @return The difference between the first two characters that differ 
 * in the strings being compared.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((s1[i] != s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/**
 * Write the string s to the file descriptor fd
 * 
 * @param s The string to be printed.
 * @param fd file descriptor
 */
void	ft_putstr_fd(const char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

/**
 * It takes two strings and joins them together.
 * 
 * @param s1 The first string to be joined.
 * @param s2 The string to be appended to the end of s1.
 * 
 * @return A pointer to a new string that is the result of the concatenation 
 * of s1 and s2.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		k;
	int		lens1;
	int		lens2;

	i = 0;
	k = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	newstr = malloc(lens1 + lens2 + 1);
	if (!newstr)
		return (NULL);
	while (s1[i])
	{
		newstr[k++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		newstr[k++] = s2[i++];
	}
	newstr[k] = '\0';
	return (newstr);
}

/**
 * It returns the length of a string.
 * 
 * @param str This is the string that we are going to find the length of.
 * 
 * @return The length of the string.
 */
size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}
