
char 	*make_new_buf(char *buf)
{
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	ft_bzero(buf);
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
	while(buf[i] && buf[i] != c )
		i++;
	// if (!buf[i])
	// 	return (0);
	return (i);
}

void	shift_buf_left(int i, char *buf)
{
	int	j;

	j = 0;
	// if (buf[i] == '\n')
		// i++;

	//move each char to the front
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
	str[newline_pos] = '\0';
	ft_bzero(str);

	ft_strlcpy(str, buf, newline_pos);

	shift_buf_left(newline_pos, buf);
	
	return (str);
}

int add_more_fd_to_buffer(char *buf, int fd)
{
	int	buf_len;
	buf_len = ft_strlen(buf);

	char *new_buf;
	new_buf = (char *)malloc((buf_len + BUFFER_SIZE + 1) * sizeof(char));
	if (!new_buf)
		return (0);
	new_buf[buf_len + BUFFER_SIZE] = '\0';		 
	ft_bzero(new_buf);

	//copy from buf to new_buf
	ft_strlcpy(new_buf, buf, buf_len);

	// flag to check EOF
	int	read_return;
	read_return = read(fd, &(new_buf[buf_len]), BUFFER_SIZE);
	// printf("%d\n", read_return);
	
	//free buf
	free(buf);
	buf = NULL;

	//assign new pointer to old buf pointer
	buf = new_buf;

	return (read_return); //return value of read()
}

char	*get_next_line(int fd)
{
	static char 	*buf;
	int				newline_pos;
	int				read_value;

	if (!buf)
		buf = make_new_buf(buf);
	newline_pos = 0;
	// read_value = 1;
	if (buf)
	{
		// read_until_newline_chr
		while (!newline_pos)
		{
			printf("buf before newline:%s\n", buf);
			newline_pos = buf_has_chr(buf, '\n');
			if (newline_pos > 0)
				break;
			// buf = add_more_fd_to_buffer(buf, fd);
			// printf("newline_pos is:%d\n", newline_pos);
			read_value = add_more_fd_to_buffer(buf, fd);
			// printf("buf after read_value:%s\n", buf);
			if (read_value == 0)
			{
				newline_pos = buf_has_chr(buf, '\n');
				if (newline_pos > 0)
					break;
				else
					return (buf);
			}
		}
		// printf("end of gnl is:%s\n", buf );
	}
	return (extracted_line(buf, newline_pos));
}