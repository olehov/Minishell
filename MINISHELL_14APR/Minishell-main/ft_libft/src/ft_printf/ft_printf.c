/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:26:13 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/24 17:26:15 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"
#include <stdlib.h>
#include <stdarg.h>

int	ft_printargs(char type, va_list args)
{
	int	count;

	count = 0;
	if (type == _percent)
		count += ft_putchar(_percent, 1);
	else if (type == _c)
		count += ft_putchar(va_arg(args, int), 1);
	else if (type == _s)
		count += ft_putstr(va_arg(args, char *), 1);
	else if (type == _p)
		count += ft_putpointer(va_arg(args, void *));
	else if (type == _d)
		count += ft_putnumb(va_arg(args, int), 1);
	else if (type == _i)
		count += ft_putnumb(va_arg(args, int), 1);
	else if (type == _u)
		count += ft_putnumb_u(va_arg(args, unsigned int), 1);
	else if (type == _x)
		count += ft_puthex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (type == _X)
		count += ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF");
	return (count);
}

int	ft_check_space(char space)
{
	if (space == _bell || space == _backspace || space == _tabh
		|| space == _endl || space == _tabv || space == _formfeed
		|| space == _carriageret)
	{
		return (1);
	}
	return (0);
}

int	ft_parceargs(char *str, va_list args)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == _percent)
		{
			count += ft_printargs(str[++i], args);
		}
		else
		{
			count += ft_putchar(str[i], 1);
		}
		i++;
	}
	if (ft_check_space(str[i]))
	{
		count += ft_putchar(str[i], 1);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	char	*str;

	count = 0;
	if (format == NULL)
	{
		return (0);
	}
	str = ft_strdup(format);
	if (str == NULL)
	{
		return (0);
	}
	va_start(args, format);
	count += ft_parceargs(str, args);
	va_end(args);
	free(str);
	return (count);
}
