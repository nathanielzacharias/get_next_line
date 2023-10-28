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

		int i;
		i = 0;
		while (i < BUFFER_SIZE)
		{
			(*buffer)[i] = 0;
			i++;
		}


		*read_bytes = read(fd, *buffer, BUFFER_SIZE);
		if (*read_bytes < 1)
			return (freed_and_nullified(buffer));
	}

	if (*buffer) //if buffer exists, find newline, if newline exists return buffer
		*nl_pos = find_newline_in(*buffer);
	
	if (*nl_pos >= 0)
		return (*buffer);

	else if (*nl_pos < 0)
	{
		// printf("in read into buf\n");
		// fflush(stdout);

		//else add to buffer

		//find len
		int len;
		len = ft_strlen(*buffer);

		//temp = malloc len + BUFSIZE
		char *temp;
		temp = malloc (len + BUFFER_SIZE + 1);
		if (!temp)
			return (NULL);
		temp[len + BUFFER_SIZE] = '\0';

		int i;
		i = 0;
		while (i < len + BUFFER_SIZE)
		{
			temp[i] = 0;
			i++;
		}

		//copy to temp from buf
		// int i;
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
		// free(temp);

		if (!len && !(*read_bytes))
			return (freed_and_nullified(buffer));
		//return buffer
		return (*buffer);
	}

	return (NULL);
}

char	*term_and_store(ssize_t *nl_pos, char **buffer, char **temp, ssize_t read_bytes)
{
	char *terminated_str;
	ssize_t	len;
	ssize_t	i;
	ssize_t	j;

	terminated_str = malloc((*nl_pos + 1) + 1);
	if (!terminated_str)
		return (NULL);
	terminated_str[(*nl_pos + 1)] = 0;

	//copy from buffer to terminated_str
	i = 0;
	while (i < (*nl_pos + 1)) //nl_pos == 0
	{
		terminated_str[i] = (*buffer)[i];
		i++;
	}

	//find buffer len from nl_pos to end
	len = (*nl_pos + 1);
	while((*buffer)[len])
		len++;			  //len == 1	
	// printf("len before -= is:%zi\n", len);
	// fflush(stdout);
	len -= (*nl_pos  ); //len == 0
	// printf("len after -= is:%zi\n", len );
	// fflush(stdout);

	//malloc temp
	*temp = malloc(len + 1);
	if (!*temp)
		return (NULL);

	//copy from buf to temp
	int offset;
	(void) read_bytes;
	// if (read_bytes <= 0)
	// {
	// 	offset = *nl_pos;
	// }
	// else
	// 	offset = *nl_pos + 1;
	offset = *nl_pos + 1;

	i = 0;
	j = (offset); //may be just *nl_pos
	while (i < len)
	{
		(*temp)[i] = (*buffer)[j];
		i++;
		j++;
	}
	(*temp)[len] = 0;
	// printf("temp is:%s\n", *temp);

	//free buffer and reassign
	free(*buffer);
	*buffer = *temp;

	return(terminated_str);
}

char *processed_line(ssize_t *nl_pos, char **buffer, char **temp, ssize_t read_bytes)
{
	if (*nl_pos == -1) //nl not found && buffer not empty so return buffer
	{
		//malloced and copied temp
		*temp = malloc(ft_strlen(*buffer) + 1);
		if (!(*temp))
			return (NULL);

		int i;
		i = 0;
		while((*buffer)[i])
		{
			(*temp)[i] = (*buffer)[i];
			i++;
		}
		(*temp)[i] = 0;


		// *temp = *buffer;
		free(*buffer);
		*buffer = NULL;
		return (*temp);
	}
	else
		return (term_and_store(nl_pos, buffer, temp, read_bytes));
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
		if ( !buffer || (read_bytes > 0 && (!buffer || *buffer == '\0')))
			return (freed_and_nullified(&buffer));
		if (nl_pos >= 0 || read_bytes <= 0)
			break ;
	}
	if (read_bytes <= 0) //eof reached or error fd
	{
		if(!(buffer) || (read_bytes == -1 && nl_pos == -1))	//reading past last line in fd
			return (freed_and_nullified(&buffer));
		else
			return (processed_line(&nl_pos, &buffer, &temp, read_bytes));
	}

	// if (read_bytes > 0)
	return (processed_line(&nl_pos, &buffer, &temp, read_bytes));
}

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
