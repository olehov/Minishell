/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:43:33 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/02 18:51:11 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

int	ft_isspace(int space)
{
	if (space == _space || space == _tabh || space == _endl
		|| space == _tabv || space == _formfeed
		|| space == _carriageret)
	{
		return (1);
	}
	return (0);
}
