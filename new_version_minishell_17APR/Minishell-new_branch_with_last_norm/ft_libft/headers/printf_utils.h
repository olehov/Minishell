/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:36 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/24 17:29:38 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_UTILS_H
# define PRINTF_UTILS_H

# include "libft.h"

/*
Parameters:
	numb: The number to output.
	
	hexbuf: The base to output in.
Return:
    len of printed number
Description:
	Outputs the number ’numb’ in hexadesimal to the given file descriptor.
*/
int	ft_puthex(unsigned int numb, char *hexbuf);
/*
Parameters:
	s: The string to output.
	
	fd: The file descriptor on which to write.
Return:
    len of printed string
Description:
	Outputs the string ’s’ to the given file descriptor.
*/
int	ft_putstr(char *s, int fd);
/*
Parameters:
	c: The character to output.
	
	fd: The file descriptor on which to write.
Return:
    len of printed character
Description:
	Outputs the character ’c’ to the given file descriptor.
*/
int	ft_putchar(char c, int fd);
/*
Parameters:
	n: The unsigned number to output.
	
	fd: The file descriptor on which to write.
Return:
    len of printed number
Description:
	Outputs the unsigned number ’n’ to the given file descriptor.
*/
int	ft_putnumb_u(unsigned int n, int fd);
/*
Parameters:
	n: The number to output.
	
	fd: The file descriptor on which to write.
Return:
    len of printed number
Description:
	Outputs the number ’n’ to the given file descriptor.
*/
int	ft_putnumb(int n, int fd);
/*
Parameters:
	ptr: The pointer to output.
Return:
    len of printed pointer
Description:
	Outputs the pointer ’ptr’ to the given file descriptor.
*/
int	ft_putpointer(void *ptr);

#endif
