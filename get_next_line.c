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

char 	*make_new_buf(void)
{
	char	*buf;

	buf = (char *)malloc((1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	// ft_bzerolen(buf, (BUFFER_SIZE));
	return (buf);
}

char *read_to_temp(char *temp, int fd, int *read_return)
{
	// free(temp);
	temp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	*read_return = read(fd, temp, BUFFER_SIZE);
	if (*read_return < 0)
		return (NULL);
	temp[*read_return] = '\0';
	return (temp);
}

int	gnl_strlen(char *str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	return(i);
}

int	find_newline_in(char *str)
{
	int i;
	i = 0;

	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i + 1);
}

char	*extract_line_from(char *buf, int fake_pos)
{
	char	*extracted_line;
	int 	i;

	extracted_line = (char *)malloc(fake_pos * sizeof(char));
	if (!extracted_line)
		return (NULL);
	extracted_line[fake_pos] = '\0';
	i = 0;
	while (i < fake_pos)
	{
		extracted_line[i] = buf[i];
		i++;
	}
	return (extracted_line);
}

char *realloc_buf(char *buf, int fake_pos)
{
	int i;
	int j;
	int len;

	i = fake_pos;
	while (buf[i] != '\0')
		i++; //confirmed i is after newline to nullterm exclusive
	len = i - (fake_pos - 1);
	char	*str;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	j = 0;
	while (j < len)
	{
		str[j] = buf[fake_pos + j];
		j++;
	}
	//free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char 	*buf;
	char			*temp;
	int				newline;
	int				read_return;
	
	if (!buf)
		buf = make_new_buf();
		// return (NULL);
	newline = 0;
	read_return = 0;
	while (!newline)
	{
		temp = read_to_temp(temp, fd, &read_return);
		if (!temp)
			return (NULL);
		buf = ft_strjoin(buf, temp);
		free(temp);
		newline = find_newline_in(buf); //indexed-1 position
		if (read_return == 0)
			break ;
	}
 	if (newline)
 	{
		temp = extract_line_from(buf, newline); //newline-1
		if (!temp)
		{
			free(buf);
			return (NULL);
		}
		buf = realloc_buf(buf, newline);
		return (temp);
 	}
	else if (read_return == 0) ///read_return < bufsize && !newline
	{
		temp = extract_line_from(buf, ft_strlen(buf) + 1);
		// free(buf);
		if (!temp)
		{
			free(buf);
			return (NULL);
		}
		// buf = realloc_buf(buf, ft_strlen(buf) + 1);
		free (buf);
		buf = NULL;
		// printf("buf is:%s\n", buf);
		return (temp);
		// return (buf);
	}
	return (NULL);
}

// #include <fcntl.h>
// int	main(void)
// {
// 	// printf("%d\n", BUFFER_SIZE );
// 	// fflush(stdout);

// 	int	fd;
// 	fd = open("nat.txt", O_RDONLY);
// 	// fd = open("empty_file.txt", O_RDONLY);
// 	// get_next_line(fd);

// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// 	printf("get_next_line is:%s", get_next_line(fd));
// }
