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

int ft_strlen(char *buf)
{
	//ft_strlen();
	int	buf_len;

	buf_len = 0;
	while (buf[buf_len])
		buf_len++;
	return (buf_len);
}

void	ft_bzero(char *str)
{
	int buf_len;
	buf_len = ft_strlen(str);

	int j;
	j = 0;
	while (j < buf_len)
	{
		str[j] = '0';
		j++;
	}
}

void	ft_strcpy(char *dest, char *src)
{
	int	src_len;
	src_len = ft_strlen(src);

	int i;
	i = 0;
	while (i < src_len)
	{
		dest[i] = src[i];
		i++;
	}
}
