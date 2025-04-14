/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:34:46 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/24 17:34:48 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"
#include <stdint.h>

static int	ft_size(uintptr_t n)
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
		n /= 16;
	}
	return (size);
}

int	ft_putpointer(void *ptr)
{
	uintptr_t	addr;
	const char	*hex_digits;
	char		hex_string[20];
	int			i;

	addr = (uintptr_t)ptr;
	hex_digits = "0123456789abcdef";
	i = ft_size(addr);
	if (addr == 0)
	{
		return (ft_putstr("(nil)", 1));
	}
	hex_string[i] = '\0';
	while (addr != 0)
	{
		hex_string[--i] = hex_digits[(addr % 16)];
		addr /= 16;
	}
	return (ft_printf("0x%s", hex_string));
}
