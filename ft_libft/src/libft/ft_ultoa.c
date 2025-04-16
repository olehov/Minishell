/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:25:23 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 10:21:56 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static int	get_size(size_t numb)
{
	int	size;

	size = 0;
	if (numb == 0)
		return (1);
	while (numb != 0)
	{
		numb /= 10;
		size++;
	}
	return (size);
}

char	*ft_ultoa(size_t numb)
{
	size_t	size;
	size_t	i;
	char	*str;

	i = 1;
	size = get_size(numb);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	while (i <= size)
	{
		str[size - i] = numb % 10 + '0';
		numb /= 10;
		i++;
	}
	str[size] = '\0';
	return (str);
}
