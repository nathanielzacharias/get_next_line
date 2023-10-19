/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:45:11 by nzachari          #+#    #+#             */
/*   Updated: 2023/10/13 13:52:08 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H



#include <unistd.h>
#include <stdlib.h>


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif //BUFFER_SIZE

char	*get_next_line(int fd);
int 	ft_strlen(char *buf);
void	ft_bzerolen(char *str, int buf_len);
void	ft_strlcpy(char *dest, char *src, int len);

#endif //GET_NEXT_LINE_H
