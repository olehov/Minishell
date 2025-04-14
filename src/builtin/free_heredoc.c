/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:11:16 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 12:51:31 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_heredoc.h"

void	free_heredoc(void *value)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)value;
	if (heredoc == NULL)
		return ;
	if (heredoc->delimiter != NULL)
		free(heredoc->delimiter);
	if (heredoc->filename != NULL)
		free(heredoc->filename);
	free(heredoc);
	value = NULL;
}
