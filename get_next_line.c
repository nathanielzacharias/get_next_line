/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:31:25 by nzachari          #+#    #+#             */
/*   Updated: 2023/10/24 10:07:22 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "get_next_line.h"

char	*read_into_buffer(char **buffer, ssize_t *nl_pos, \
	ssize_t *read_bytes, int fd)
{
	int		len;
	char	*temp;
	ssize_t	i;

	if (!(*buffer))
	{
		*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		*read_bytes = read(fd, *buffer, BUFFER_SIZE);
		if (*read_bytes < 1)
			return (freed_and_nullified(buffer));
	}
	*nl_pos = find_newline_in(*buffer);
	if (*nl_pos >= 0)
		return (*buffer);
	len = ft_strlen(*buffer);
	temp = ft_calloc(len + BUFFER_SIZE + 1, sizeof(char));
	i = -1;
	while (temp && (++i < len))
		temp[i] = (*buffer)[i];
	*read_bytes = read(fd, &temp[i], BUFFER_SIZE);
	free(*buffer);
	*buffer = temp;
	if (!len && !(*read_bytes))
		return (freed_and_nullified(buffer));
	return (*buffer);
}

char	*term_and_store(ssize_t *nl_pos, char **buffer, char **temp, \
	char *terminated_str)
{
	ssize_t	len;
	ssize_t	i;
	ssize_t	j;

	len = (*nl_pos + 1);
	while ((*buffer)[len])
		len++;
	len -= (*nl_pos);
	*temp = malloc(len + 1);
	if (!*temp)
		return (NULL);
	i = -1;
	j = (*nl_pos + 1);
	while (++i < len)
	{
		(*temp)[i] = (*buffer)[j];
		j++;
	}
	(*temp)[len] = 0;
	free(*buffer);
	*buffer = *temp;
	return (terminated_str);
}

char	*processed_line(ssize_t *nl_pos, char **buffer, char **temp)
{
	ssize_t	i;
	char	*terminated_str;

	if (*nl_pos == -1)
	{
		*temp = malloc(ft_strlen(*buffer) + 1);
		if (!(*temp))
			return (NULL);
		i = -1;
		while ((*buffer)[++i])
			(*temp)[i] = (*buffer)[i];
		(*temp)[i] = 0;
		free(*buffer);
		*buffer = NULL;
		return (*temp);
	}
	terminated_str = malloc((*nl_pos + 1) + 1);
	if (!terminated_str)
		return (NULL);
	terminated_str[(*nl_pos + 1)] = 0;
	i = -1;
	while (++i < (*nl_pos + 1))
		terminated_str[i] = (*buffer)[i];
	return (term_and_store(nl_pos, buffer, temp, terminated_str));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp;
	ssize_t		nl_pos;
	ssize_t		read_bytes;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	nl_pos = -1;
	read_bytes = -1;
	while (1)
	{
		buffer = read_into_buffer(&buffer, &nl_pos, &read_bytes, fd);
		if (!buffer || (read_bytes > 0 && (!buffer || *buffer == '\0')))
			return (freed_and_nullified(&buffer));
		if (nl_pos >= 0 || read_bytes <= 0)
			break ;
	}
	if (read_bytes <= 0)
	{
		if (!(buffer) || (read_bytes == -1 && nl_pos == -1))
			return (freed_and_nullified(&buffer));
		else
			return (processed_line(&nl_pos, &buffer, &temp));
	}
	return (processed_line(&nl_pos, &buffer, &temp));
}
/*
// #include <fcntl.h>
// int	main(void)
// {
// 	// printf("%d\n", BUFFER_SIZE );
// 	// fflush(stdout);
// 	int	fd;
// 	// fd = open("nat.txt", O_RDONLY);
// 	fd = open("1char.txt", O_RDONLY);
// 	// fd = open("empty_file.txt", O_RDONLY);

// 	int i = -1;
// 	while (++i < 9)
// 	{
// 		char *test = get_next_line(fd);
// 		printf("get_next_line is:%s", test);
// 		fflush(stdout);
// 		free(test);
// 	}
// 	close(fd);
// }
*/
