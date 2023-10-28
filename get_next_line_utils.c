/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:44:03 by nzachari          #+#    #+#             */
/*   Updated: 2023/10/13 13:44:54 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		++len;
	return (len);
}

char *freed_and_nullified(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (*ptr);
}

ssize_t	find_newline_in(char *str)
{
	ssize_t i;
	i = 0;

	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (-1);
	else 
		return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)s;
	while (i < n)
	{
		a[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	array = malloc (nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, nmemb * size);
	return (array);
}



// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	len;
// 	size_t	i;
// 	size_t	j;

// 	len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	str = (char *)malloc(len * sizeof(char));
// 	if (!str)
// 		return (NULL);
	
// 	//copy from s1 to str
// 	i = 0;
// 	while (i < ft_strlen((char *)s1))
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}

// 	//copy from s2 to str
// 	j = 0;
// 	while (j < ft_strlen((char *)s2))
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}

// 	//null terminate
// 	str[i + j] = '\0';

	
// 	return (str);
// }