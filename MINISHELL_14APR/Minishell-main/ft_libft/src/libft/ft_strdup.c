/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:01:18 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/12 11:18:41 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../headers/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*copy;

	size = ft_strlen(s) + 1;
	copy = (char *)malloc((size) * sizeof(char));
	if (copy == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(copy, s, size);
	return (copy);
}
