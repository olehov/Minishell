/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_row_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:57:01 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/10 16:57:26 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

size_t	get_row_size(char **args)
{
	size_t	i;

	i = 0;
	if (args == NULL || *args == NULL)
	{
		return (0);
	}
	while (args[i] != NULL)
	{
		i++;
	}
	return (i);
}
