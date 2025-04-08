/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:20:08 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/07 12:52:32 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEREDOC_H
# define FT_HEREDOC_H

# include "minishell.h"

# define HEREDOC_FILENAME_PATH "/tmp/heredoc_tmp_"

typedef struct s_heredoc
{
	char	*filename;
	char	*delimiter;
}	t_heredoc;

t_heredoc	*init_heredoc(char *dilimiter);

int			ft_heredoc(t_heredoc *heredoc, t_list *env);

void		unlink_heredocs(t_list **heredocs);
void		free_heredoc(void *heredoc);
#endif