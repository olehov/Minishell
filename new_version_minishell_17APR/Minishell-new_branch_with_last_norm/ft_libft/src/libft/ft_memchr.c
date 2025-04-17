/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:30:43 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/12 11:31:32 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	if (n != 0)
	{
		if (str[i] == c)
		{
			return ((char *)str);
		}
		while (i < n)
		{
			if (*str == (unsigned char)c)
			{
				return (str);
			}
			i++;
			str++;
		}
	}
	return (NULL);
}
