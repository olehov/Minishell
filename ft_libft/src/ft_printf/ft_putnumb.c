/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:13 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/24 17:29:17 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/printf_utils.h"

static int	ft_size(int n, int sign)
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
	if (sign == -1)
	{
		return (size + 1);
	}
	return (size);
}

int	ft_putnumb(int n, int fd)
{
	ft_putnbr_fd(n, fd);
	if (n < 0)
	{
		return (ft_size(n, -1));
	}
	return (ft_size(n, 1));
}
