/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:27:43 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 10:37:02 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include <stdint.h>
#include <limits.h>

static int	ft_ismin(long *nb)
{
	if (*nb == LONG_MIN)
	{
		*nb += 1;
		return (1);
	}
	return (0);
}

static int	ft_size(long n, int sign)
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

static int	ft_sign(int n)
{
	if (n >= 0)
	{
		return (1);
	}
	else
	{
		return (-1);
	}
}

static char	*ft_min(char *s, int size, int sign, int ismin)
{
	if (sign == -1)
	{
		if (ismin == 1)
		{
			s[size - 1] += 1;
		}
		s[0] = '-';
	}
	return (s);
}

char	*ft_ltoa(long n)
{
	char	*number;
	int		sign;
	int		size;
	int		size2;
	int		ismin;

	sign = ft_sign(n);
	ismin = ft_ismin(&n);
	size = ft_size(n, sign);
	n *= sign;
	size2 = size;
	number = (char *)malloc(sizeof(char) * (size + 1));
	if (number == NULL)
		return (NULL);
	if (n == 0)
		number[0] = n + '0';
	while (n != 0)
	{
		number[--size] = (n % 10) + '0';
		n /= 10;
	}
	number[size2] = '\0';
	number = ft_min(number, size2, sign, ismin);
	return (number);
}
