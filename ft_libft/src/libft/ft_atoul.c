/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:11:25 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 10:22:44 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include <stdint.h>

//Return -1 is more than max
static int	is_max(const char *str, size_t len)
{
	size_t	max_len;
	char	*numb_max;

	numb_max = ft_ultoa(SIZE_MAX);
	if (numb_max == NULL)
		return (-1);
	max_len = ft_strlen(numb_max);
	len = ft_strlen(str);
	if (len > max_len)
		return (free(numb_max), -1);
	else if (len < max_len)
		return (free(numb_max), 1);
	len = 0;
	while (len < max_len)
	{
		if (str[len] > numb_max[len])
			return (free(numb_max), -1);
		len++;
	}
	return (free(numb_max), 1);
}

static int	is_all_digit(const char *str, size_t len)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (i < len)
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

size_t	ft_atoul(const char *str)
{
	size_t	result;
	size_t	i;
	size_t	str_len;

	result = 0;
	i = 0;
	str_len = ft_strlen(str);
	if (is_all_digit(str, str_len) == -1 || is_max(str, str_len) == -1)
		return (0);
	while (i < str_len)
	{
		if (str[i + 1] != '\0')
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
	return (result);
}
