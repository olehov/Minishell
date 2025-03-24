/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:30:41 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/12 12:30:43 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../headers/libft.h"

static int	ft_check_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_checkstart(const char *s1, const char *set, size_t start)
{
	while (s1[start] && ft_check_set(s1[start], set))
	{
		start++;
	}
	return (start);
}

static size_t	ft_checkend(const char *s1, const char *set,
							size_t start, size_t end)
{
	while (end > start && ft_check_set(s1[end - 1], set))
	{
		end--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = ft_checkstart(s1, set, 0);
	end = ft_checkend(s1, set, start, ft_strlen(s1));
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (str == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (start < end)
	{
		str[i++] = s1[start++];
	}
	str[i] = 0;
	return (str);
}
