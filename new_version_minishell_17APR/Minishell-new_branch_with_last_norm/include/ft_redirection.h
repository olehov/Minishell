/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:19:48 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:53:51 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REDIRECTION_H
# define FT_REDIRECTION_H

# include "minishell.h"
# include "ft_minishell_types.h"

/**
 * @brief Initializes a redirection structure with
 * the specified filename and type.
 * 
 * @param filename The target file name for redirection.
 * @param type Type of redirection (input, output, append, heredoc).
 * @return Pointer to a newly allocated t_redirect structure.
 */
t_redirect	*init_redirect(char *filename, t_redirect_type type);

/**
 * @brief Handles all redirections for a given command.
 * Opens files and adjusts file descriptors accordingly.
 * 
 * @param cmd Pointer to the command node containing redirection list.
 * @return 0 on success, non-zero on failure (e.g., permission denied).
 */
int			handle_redirect(t_cmd *cmd);

/**
 * @brief Frees memory allocated for a redirection structure.
 * 
 * @param redirect Pointer to the redirection structure to free.
 */
void		free_redirect(void *redirect);

#endif