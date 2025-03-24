/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:46:57 by ogrativ           #+#    #+#             */
/*   Updated: 2024/07/02 12:47:01 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_free_2d_array(char **arr, int row)
{
	int	i;

	i = 0;
	if (*arr == NULL)
	{
		return ;
	}
	while (i < row)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
