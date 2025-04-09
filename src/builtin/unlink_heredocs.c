/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:32:11 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 20:15:01 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_heredoc.h"

void	unlink_heredocs(t_list **heredocs)
{
	t_list		*node;
	t_heredoc	*heredoc_node;

	node = *heredocs;
	if (node == NULL)
		return ;
	while (node)
	{
		heredoc_node = node->content;
		unlink(heredoc_node->filename);
		node = node->next;
	}
	ft_lstclear(heredocs, free_heredoc);
}
