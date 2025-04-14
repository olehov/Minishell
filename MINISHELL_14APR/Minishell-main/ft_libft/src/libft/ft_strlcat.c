/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:03:37 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/12 11:11:15 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include <stdio.h>

static void	ft_strcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	i = 0;
	while (src[i] != 0 && dstlen < size - 1)
	{
		dst[dstlen++] = src[i++];
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	totallen;
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	totallen = dstlen + srclen;
	if (dst != NULL && size == 0)
	{
		return (srclen);
	}
	if (size <= dstlen)
	{
		return (srclen + size);
	}
	if (totallen + 1 < size)
	{
		ft_strcat(dst, src, size);
	}
	else if (size != 0)
	{
		ft_strcat(dst, src, size);
		dst[totallen] = '\0';
	}
	return (totallen);
}
