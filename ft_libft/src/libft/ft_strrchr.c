/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:09:27 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/12 11:12:19 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*first;

	first = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			first = (char *)s;
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	if (first != NULL)
	{
		return ((char *)first);
	}
	return (NULL);
}
