/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:19:48 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/08 16:34:29 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REDIRECTION_H
# define FT_REDIRECTION_H

# include "minishell.h"


typedef struct s_cmd	t_cmd;

/**
 * @param _redirect_in <
 * @param _redirect_out >
 * @param _heredoc <<
 * @param _append_to_file >>
 */
typedef enum e_redirect_type
{
	_reset = 0,
	_redirect_in = 1,
	_redirect_out = 2,
	_heredoc = 3,
	_append_to_file = 4
}	t_redirect_type;

/**
 * @param filename - pointer to name of file
 * @param type - type of reddirection
 */
typedef struct s_redirect
{
	char			*filename;
	t_redirect_type	type;
}	t_redirect;

t_redirect	*init_redirect(char *filename, t_redirect_type type);

void		handle_redirects(t_cmd *cmd);

void		free_redirect(void *redirect);

#endif