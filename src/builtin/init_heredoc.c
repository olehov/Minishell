/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:47:16 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 20:14:40 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_heredoc.h"

t_heredoc	*init_heredoc(char *dilimiter)
{
	static int	index = 0;
	t_heredoc	*heredoc;
	char		*str_index;

	heredoc = malloc(sizeof(t_heredoc));
	if (heredoc == NULL)
		return (NULL);
	str_index = ft_itoa(index);
	if (str_index == NULL)
		return (free_heredoc(heredoc), NULL);
	heredoc->filename = ft_strjoin3(HEREDOC_FILENAME_PATH, str_index, ".tmp");
	if (heredoc->filename == NULL)
		return (free(str_index), free_heredoc(heredoc), NULL);
	free(str_index);
	heredoc->delimiter = ft_strdup(dilimiter);
	if (heredoc->delimiter == NULL)
		return (free_heredoc(heredoc), NULL);
	return (heredoc);
}
