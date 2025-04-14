/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:42:05 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 16:59:51 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_H
# define FT_CMD_H

# include "../ft_libft/headers/libft.h"
# include "ft_minishell_types.h"
// # include "./minishell.h"

t_cmd	*init_cmd_node(void);

/**
 * @param cmd Pointer to current cmd node
 * @param type Redirection type from e_redirectind_type enum
 */
void	add_redirection(t_cmd *cmd, t_redirect_type type, char *path);

t_cmd	*get_cmd_lst(t_minish *msh);

void	free_cmd_node(t_cmd *cmd);
void	free_cmd_list(t_cmd **cmd);

#endif