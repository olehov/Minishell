/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:29:53 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/15 13:29:56 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	if (lst == NULL)
	{
		return (NULL);
	}
	node = lst;
	while (node != NULL)
	{
		if (node->next == NULL)
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}
