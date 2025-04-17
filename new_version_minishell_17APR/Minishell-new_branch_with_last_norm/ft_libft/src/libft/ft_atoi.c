/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:52:09 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/12 11:26:47 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/libft.h"

static int	ft_skipspace(const char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v')
	{
		i++;
	}
	return (i);
}

static int	ft_sign(const char *str, int *sign, int i)
{
	if (str[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else
	{
		*sign = 1;
		if (str[i] == '+')
		{
			i++;
		}
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	i = ft_sign(str, &sign, ft_skipspace(str, 0));
	while (ft_isdigit(str[i]))
	{
		if (str[i + 1] != '\0' && ft_isdigit(str[i + 1]))
		{
			result += str[i] - '0';
			result *= 10;
		}
		else
		{
			result += str[i] - '0';
		}
		i++;
	}
	return (result * sign);
}
