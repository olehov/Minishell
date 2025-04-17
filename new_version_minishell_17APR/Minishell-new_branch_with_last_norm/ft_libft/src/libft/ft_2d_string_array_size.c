/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_string_array_size.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:03:16 by ogrativ           #+#    #+#             */
/*   Updated: 2024/07/10 13:03:18 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

int	ft_2d_string_array_size(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[count] != NULL)
	{
		while (str[count][i] != '\0')
		{
			i++;
		}
		count++;
		i = 0;
	}
	return (count);
}
