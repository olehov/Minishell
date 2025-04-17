/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:19:07 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/12 11:20:55 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		sizes1;
	int		sizes2;
	int		totalsize;

	if (s1 == NULL && s2 == NULL)
	{
		return (NULL);
	}
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	totalsize = sizes1 + sizes2;
	res = (char *)malloc(sizeof(char) * totalsize + 1);
	if (res == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(res, s1, sizes1 + 1);
	ft_strlcat(res, s2, (totalsize + 1));
	return (res);
}
