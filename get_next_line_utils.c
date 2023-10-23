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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	
	//copy from s1 to str
	i = 0;
	while (i < ft_strlen((char *)s1))
	{
		str[i] = s1[i];
		i++;
	}

	//copy from s2 to str
	j = 0;
	while (j < ft_strlen((char *)s2))
	{
		str[i + j] = s2[j];
		j++;
	}

	//null terminate
	str[i + j] = '\0';

	
	return (str);
}

void	ft_bzerolen(char *str, int buf_len)
{
	int	j;
	j = 0;
	while (j < buf_len)
	{
		str[j] = 0;
		j++;
	}
}
