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
	ft_bzerolen(buf, (BUFFER_SIZE));
	return (buf);
}

char *read_to_temp(char *temp, int fd, int *read_return)
{
	// free(temp);
	temp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	temp[BUFFER_SIZE] = '\0';

	// int ret = 0;
	*read_return = read(fd, temp, BUFFER_SIZE);
	printf("temp is: %s\n", temp);
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

// char	*gnl_strcat(char *s1, char *s2)
// {
// 	int len_s1;
// 	int	len_s2;

// 	len_s1 = gnl_strlen(s1);
// 	len_s2 = gnl_strlen(s2);

// 	char *str;
// 	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	str[len_s1 + len_s2] = '\0';
// 	int i;
// 	i = 0;
// 	while (i < len_s1)
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (i < len_s1 + len_s2)
// 	{
// 		str[i] = s2[i - len_s1];
// 		i++;
// 	}
// 	// free(s2);
// 	return (str);
// }
static size_t	thislen(char const *str)
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

	len = thislen(s1) + thislen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen((char *)s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen((char *)s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}



int	find_newline_in(char *str)
{
	int i;
	i = 0;


	// printf("buf string is:%s\n", str);
	// printf("%s\n", "here in find nl" );
	// fflush(stdout);

	// printf("i pre while: %d\n", i );
	// fflush(stdout);
	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	// printf("i post while: %d\n", i );
	// fflush(stdout);
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
	printf("buf pointer is:%p\n", buf );
	fflush(stdout);
	newline = 0;
	read_return = 1;
	while (!newline && read_return > 0)
	{
		temp = read_to_temp(temp, fd, &read_return);
		printf("rr is:%d\n", read_return );
		printf("temp post read to temp is: %s\n",  temp);
		buf = ft_strjoin(buf, temp);
		printf("buf post join is:%s\n", buf );
		fflush(stdout);
		// buf = temp;

		// free(temp);
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
	// printf("%s\n", "here in main" );

	int	fd;
	fd = open("nat.txt", O_RDONLY);
	// fd = open("empty_file.txt", O_RDONLY);
	// get_next_line(fd);

	fflush(stdout);


	printf("get_next_line is:%s\n", get_next_line(fd));
}
