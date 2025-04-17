/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:44:36 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/15 11:44:39 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include <unistd.h>

int	is_min(int *nb)
{
	if (*nb == -2147483648)
	{
		*nb += 1;
		return (1);
	}
	return (0);
}

int	is_negative(int *nb, int fd)
{
	if (*nb < 0)
	{
		ft_putchar_fd('-', fd);
		return (-1);
	}
	return (1);
}

void	print(char buffer[], int i, int ismin, int fd)
{
	while (i > 0)
	{
		if (ismin == 1 && i == 1)
		{
			ft_putchar_fd(buffer[--i] + 1, fd);
		}
		else
		{
			ft_putchar_fd(buffer[--i], fd);
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buffer[12];
	int		i;
	int		ismin;

	i = 0;
	ismin = is_min(&n);
	n *= is_negative(&n, fd);
	if (n == 0)
	{
		write(fd, "0", 1);
	}
	while (n != 0)
	{
		buffer[i++] = '0' + n % 10;
		n /= 10;
	}
	print(buffer, i, ismin, fd);
}
