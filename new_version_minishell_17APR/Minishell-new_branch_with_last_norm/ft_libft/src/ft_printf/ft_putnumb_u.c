/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumb_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:31:08 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/24 17:31:11 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/printf_utils.h"
#include <stdlib.h>

static int	ft_size(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
	{
		return (1);
	}
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static void	ft_putnbr_uns(unsigned int n, int fd)
{
	char	*buffer;
	int		size;

	size = ft_size(n);
	buffer = ft_calloc(sizeof(char), size + 1);
	if (buffer == NULL)
	{
		return ;
	}
	if (n == 0)
	{
		buffer[0] = '0';
	}
	buffer[size] = '\0';
	while (n != 0)
	{
		buffer[--size] = '0' + n % 10;
		n /= 10;
	}
	ft_putstr(buffer, fd);
	free(buffer);
}

int	ft_putnumb_u(unsigned int n, int fd)
{
	ft_putnbr_uns(n, fd);
	return (ft_size(n));
}
