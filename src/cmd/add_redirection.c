/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:32:13 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/17 22:01:22 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_cmd.h"
#include "../../include/minishell.h"

void	add_redirection(t_cmd *cmd, t_redirect_type type, char *path)
{
	char	*filename;

	if (cmd == NULL || path == NULL)
		return ;
	// printf("path: %s\n", path);
	filename = remove_quotes(path);
	// printf("filename: %s\n\n", filename);
	if (filename == NULL)
		return ;
	if (cmd->redirect_lst == NULL)
		cmd->redirect_lst = ft_lstnew(
				init_redirect(filename, type));
	else
		ft_lstadd_back(&cmd->redirect_lst,
			ft_lstnew(init_redirect(filename, type)));
	free(filename);
}
