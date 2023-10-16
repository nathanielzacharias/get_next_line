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

char 	*make_new_buf(char *buf)
{
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	// int i;
	// i = 0;
	// while(i < BUFFER_SIZE)
	// {
	// 	buf[i] = '0';
	// 	i++;
	// }
	// buf[BUFFER_SIZE] = '\0';
	return (buf);
}

int	buf_has_chr(char *buf, char c)
{
	int	i;

	i = 0;
	while(buf[i] && buf[i] != c)
		i++;
	if (!buf[i])
		return (0);
	return (i);
}

void	shift_buf_left(int i, char *buf)
{
	int	j;

	j = 0;
	if (buf[i] == '\n')
		i++;
	while (buf[i] != '\0')
	{
		buf[j] = buf[i];
		j++;
		i++;
	}
	buf[j] = '\0';
}

char	*extracted_line(char *buf, int newline_pos)
{
	char	*str;
	int		i;

	str = (char *)malloc((newline_pos + 1) * sizeof(char));
	if (!str)
		return (NULL);
	int j;
	j = 0;
	while (j < newline_pos)
	{
		str[j] = '0';
		j++;
	}
	str[newline_pos] = '\0';
	i = 0;
	while (i < newline_pos)
	{
		str[i] = buf[i];
		i++;
	}
	shift_buf_left(newline_pos, buf);
	return (str);
}

char	*add_more_fd_to_buffer(char *buf, int fd)
{
	//buf_len();
	int	buf_len;
	buf_len = 0;
	while (buf[buf_len])
		buf_len++;
	//malloc (buf_len + BUFFER_SIZE + 1) * sizeof(char);
	char *new_buf;
	new_buf = (char *)malloc((buf_len + BUFFER_SIZE + 1) * sizeof(char));
	if (!new_buf)
		return (NULL);
	int j;
	j = 0;
	while (j < buf_len + BUFFER_SIZE)
	{
		new_buf[j] = '0';
		j++;
	}
	new_buf[buf_len + BUFFER_SIZE] = '\0';		 

	//copy_buf, read_to_buf, add 0
	int i;
	i = 0;
	while(i < buf_len)
	{
		new_buf[i] = buf[i];
		i++;
	}
	read(fd, &new_buf[i], BUFFER_SIZE);
	//free buf
	free(buf);
	//assign new pointer to old buf pointer
	buf = new_buf;
	return (buf); //return new_buf
}

char	*get_next_line(int fd)
{
	static char 	*buf;
	int				newline_pos;
	// int				eof_pos;

	if (!buf)
		buf = make_new_buf(buf);

	newline_pos = 0;
	
	// while (!newline_pos)
	// {
		newline_pos = buf_has_chr(buf, '\n');
		if (newline_pos)
		{
			return (extracted_line(buf, newline_pos));
			// else if (eof_pos)
			// 	return extracted_line(buf, eof_pos);
		}
		else if (!newline_pos)
		{
			// buf = add_more_fd_to_buffer(buf, fd);
			// newline_pos = buf_has_chr(buf, '\n');
			// while (!newline_pos)
			// {
				buf = add_more_fd_to_buffer(buf, fd);
				newline_pos = buf_has_chr(buf, '\n');
			// }
			// if (newline_pos)
				return (extracted_line(buf, newline_pos));
			// else if (!newline_pos)
			// 	buf = add_more_fd_to_buffer(buf, fd);
		}
		return extracted_line(buf, newline_pos);
	// }
}

#include <fcntl.h>

int	main(void)
{
	int	fd;
	fd = open("nat.txt", O_RDONLY);
	// fd = open("empty_file.txt", O_RDONLY);
	// get_next_line(fd);

	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	printf("get_next_line is:%s\n", get_next_line(fd));
	// printf("get_next_line is:%s\n", get_next_line(fd));
	// printf("get_next_line is:%s\n", get_next_line(fd));
	// printf("get_next_line is:%s\n", get_next_line(fd));
	// printf("get_next_line is:%s\n", get_next_line(fd));
}
