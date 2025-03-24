/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:30:20 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/24 17:30:22 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/printf_utils.h"

int	ft_putstr(char *s, int fd)
{
	int		size;

	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (ft_strlen("(null)"));
	}
	size = ft_strlen(s);
	ft_putstr_fd(s, fd);
	return (size);
}
