/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:08:08 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/15 11:08:09 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	size;

	i = 0;
	if (s == NULL)
	{
		return ;
	}
	size = ft_strlen(s);
	while (i < size)
	{
		f(i, &s[i]);
		i++;
	}
	s[size] = '\0';
}
