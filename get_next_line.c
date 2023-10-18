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

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	ft_bzerolen(buf, (BUFFER_SIZE + 1));
	return (buf);
}

int	read_to_temp(char *temp, int fd)
{
	// free(temp);
	temp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (-1);
	temp[BUFFER_SIZE] = '\0';
	return (read(fd, temp, BUFFER_SIZE));
}

int	gnl_strlen(char *str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	return(i);
}

char	*gnl_strcat(char *s1, char *s2)
{
	int len_s1;
	int	len_s2;

	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);

	char *str;
	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len_s1 + len_s2] = '\0';
	int i;
	i = 0;
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len_s1 + len_s2)
	{
		str[i] = s2[i - len_s1];
		i++;
	}
	// free(s2);
	return (str);
}

int	find_newline_in(char *str)
{
	int i;
	i = 0;

	while (str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (0);
	return (i + 1);
}

char	*extract_line_from(char *buf, int fake_pos)
{
	char *extracted_line;
	int i;

	extracted_line = (char *)malloc(fake_pos * sizeof(char));
	if (!extracted_line)
		return (NULL);
	extracted_line[fake_pos] = '\0';
	
	i = 0;
	while (i < fake_pos)
		extracted_line[i] = buf[i];
	extracted_line[fake_pos] = '\0';

	return (extracted_line);
}

char *realloc_buf(char *buf, int fake_pos)
{
	int i;
	i = fake_pos;
	while (buf[i] != '\0')
		i++;
	
	int len;
	len = i - fake_pos;

	char	*str;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';

	while (i >= fake_pos)
	{
		str[i] = buf[i];
		i--; 
	}

	free(buf);

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
	newline = 0;
	read_return = 1;
	while (!newline && read_return > 0)
	{
		read_return = read_to_temp(temp, fd);
		temp = gnl_strcat(buf, temp);
		free(buf);
		buf = temp;
		free(temp);
		newline = find_newline_in(buf); //indexed-1 position
	}
	if (read_return == -1)
	{
		// free(buf);
		return (NULL);
	}
 	if (newline)
 	{
		temp = extract_line_from(buf, newline); //newline-1
		if (!temp)
		{
			// free(buf);
			return (NULL);
		}
		buf = realloc_buf(buf, newline);
		return (temp);
 	}
	else if (read_return == 0)
		return (buf);
	return (NULL);
}

#include <fcntl.h>
int	main(void)
{
	int	fd;
	fd = open("nat.txt", O_RDONLY);
	// fd = open("empty_file.txt", O_RDONLY);
	// get_next_line(fd);

	printf("get_next_line is:%s\n", get_next_line(fd));
}
