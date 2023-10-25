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
# define BUFFER_SIZE 5
#endif //BUFFER_SIZE

char	*get_next_line(int fd);
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_bzerolen(char *str, int buf_len);

#endif //GET_NEXT_LINE_H
