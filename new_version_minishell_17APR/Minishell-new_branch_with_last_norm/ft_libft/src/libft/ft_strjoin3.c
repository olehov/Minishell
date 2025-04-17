/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:56 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/22 17:24:29 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	*ft_strjoin3(const char *dest, const char *str2, const char *str3)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dest == NULL || str2 == NULL || str3 == NULL)
		return (NULL);
	str = malloc(ft_strlen(dest) + ft_strlen(str2) + ft_strlen(str3) + 1);
	if (str == NULL)
		return (NULL);
	while (dest[i] != '\0')
		str[i++] = dest[j++];
	j = 0;
	while (str2[j] != '\0')
		str[i++] = str2[j++];
	j = 0;
	while (str3[j] != '\0')
		str[i++] = str3[j++];
	str[i] = '\0';
	return (str);
}
