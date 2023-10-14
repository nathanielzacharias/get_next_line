/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:41:29 by nzachari          #+#    #+#             */
/*   Updated: 2023/10/14 16:44:12 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	find_newline_char(int fd)
{
	char	*str;
	int		count;
	int		read_ret;

	str = malloc((1) * sizeof(char));
	if (!str)
		return (0);
	count = 0;
	while (*str != '\n' )// || *str != '\0')
	{ 
		read_ret = read(fd, str, 1);
		printf("read_ret is: %i\n", read_ret);	
		if (read_ret < 1)
		{
			// free(str);
			// return (1995);
			break ;
		}
		else
			count++;
	}
	free(str);
	return (count);
}

char	*return_line(size_t count, int fd, char *str)
{
	size_t	i;
	int		read_ret;

	str = malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < count)
	{
		read_ret = read(fd, (str + i), 1);
		if (read_ret < 1)
		{
			free (str);
			return (NULL);
		}
		else
			i++;
	}
	str[count] = 0;
	write(1, str, count);
	return (str);
}

char	*get_next_line(int fd)
{
	char	*str;
	size_t	count;
	int		check;

	count = 0;
	count += find_newline_char(fd);
	printf("%li\n", count);
	str = return_line(count, fd, str);
	// if (!str)
	// 	return (NULL); 
	return (str);
}

#include <fcntl.h>

int	main(void)
{
	int	fd;
	fd = open("nat.txt", O_RDONLY);
	// fd = open("empty_file.txt", O_RDONLY);
	get_next_line(fd);
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));
	// printf("%s\n", get_next_line(fd));

}
