/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:46:57 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 16:49:55 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	if (str == NULL || *str == NULL)
	{
		return ;
	}
	while (str[i] != NULL)
	{
		free(str[i++]);
	}
	free(str);
}
