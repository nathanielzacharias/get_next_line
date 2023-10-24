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

ssize_t	find_newline_in(char *str)
{
	ssize_t i;
	i = 0;

	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

// size_t	ft_strlen(char const *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (*str++)
// 		++len;
// 	return (len);
// }

char	*read_into_buffer(char **buffer, ssize_t *nl_pos, ssize_t *read_bytes, int fd)
{

	if (!(*buffer)) //if buffer doesnt exist, malloc buffer_size
	{
		*buffer = malloc(BUFFER_SIZE + 1);
		if(!(*buffer))
			return(NULL);
		(*buffer)[BUFFER_SIZE] = 0;

		*read_bytes = read(fd, *buffer, BUFFER_SIZE);
	}

	// printf("in read into buf\n");
	// fflush(stdout);

	if (*buffer) //if buffer exists, find newline, if newline exists return buffer
	{
		*nl_pos = find_newline_in(*buffer);
		if (*nl_pos >= 0)
			return (*buffer);
	}

	//else add to buffer

	//find len
	int len;
	len = ft_strlen(*buffer);

	//temp = malloc len + BUFSIZE
	char *temp;
	temp = malloc (len + BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	temp[len + BUFFER_SIZE] = 0;

	//copy to temp from buf
	int i;
	i = 0;
	while (i < len)
	{
		temp[i] = (*buffer)[i];
		i++;
	}

	//read from fd to end of temp
	*read_bytes = read(fd, &temp[i], BUFFER_SIZE);

	//free buff, assign temp to buf
	free(*buffer);
	*buffer = temp;

	//return buffer
	return (*buffer);
}

char	*term_and_store(ssize_t *nl_pos, char **buffer, char **temp)
{
	char *terminated_str;
	size_t	len;
	size_t	i;
	size_t	j;

	terminated_str = malloc((*nl_pos + 1) + 1);
	if (!terminated_str)
		return (NULL);
	terminated_str[(*nl_pos + 1)] = 0;

	//copy from buffer to terminated_str
	i = 0;
	while (i < (*nl_pos + 1))
	{
		terminated_str[i] = (*buffer)[i];
		i++;
	}

	//find buffer len from nl_pos to end
	len = (*nl_pos + 1);
	while((*buffer)[len])
		len++;
	len -= (*nl_pos + 1);

	//malloc temp
	*temp = malloc(len + 1);
	if (!*temp)
		return (NULL);

	//copy from buf to temp
	i = 0;
	j = (*nl_pos + 1);
	while (i < len)
	{
		(*temp)[i] = (*buffer)[j];
		i++;
		j++;
	}
	(*temp)[len] = 0;

	//free buffer and reassign
	free(*buffer);
	*buffer = *temp;

	return(terminated_str);
}

char *processed_line(ssize_t *nl_pos, char **buffer, char **temp)
{
	if (*nl_pos == -1) //nl not found && buffer not empty so return buffer
		return (*buffer);
	else
		return (term_and_store(nl_pos, buffer, temp));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp;
	ssize_t		nl_pos;
	ssize_t		read_bytes;

	nl_pos = -1;
	read_bytes = -1;

	while (1)
	{
		// printf("here in while 1\n");
		// fflush(stdout);
		buffer = read_into_buffer(&buffer, &nl_pos, &read_bytes, fd);
		if (nl_pos >= 0)
			break ;
		else if (read_bytes <= 0)
			break ;
	}
	

	if (read_bytes == 0) //eof reached
	{
		if(!(*buffer))		//reading past last line in fd
			return (NULL);
		return (processed_line(&nl_pos, &buffer, &temp));
	}

	// printf("here between ifs\n");
	// fflush(stdout);

	else if (read_bytes == -1) //fd error
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}

	// if (read_bytes > 0)
	return (processed_line(&nl_pos, &buffer, &temp));
}

#include <fcntl.h>
int	main(void)
{
	// printf("%d\n", BUFFER_SIZE );
	// fflush(stdout);
	int	fd;
	fd = open("nat.txt", O_RDONLY);
	// fd = open("empty_file.txt", O_RDONLY);

	int i = -1;
	while (++i < 10)
	{
		char *test = get_next_line(fd);
		printf("get_next_line is:%s", test);
		fflush(stdout);
		free(test);
	}

	close(fd);
}