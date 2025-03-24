/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:53:09 by ogrativ           #+#    #+#             */
/*   Updated: 2024/05/22 16:20:46 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

/*
Return a next line from file (fd)
*/
char	*get_next_line(int fd);

char	*ft_join_and_free(char *dest, char *src);

#endif
