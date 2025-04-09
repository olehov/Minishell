/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:19:48 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 13:19:01 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REDIRECTION_H
# define FT_REDIRECTION_H

# include "minishell.h"
# include "ft_minishell_types.h"

t_redirect	*init_redirect(char *filename, t_redirect_type type);

void		handle_redirects(t_cmd *cmd);

void		free_redirect(void *redirect);

#endif