/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:01:48 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:53:10 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_cmd.h"
#include "../../include/ft_redirection.h"

void	free_cmd_node(t_cmd *cmd)
void	free_cmd_node(t_cmd *cmd)
{
	size_t	i;
	size_t	i;

	i = 0;
	if (cmd == NULL)
	i = 0;
	if (cmd == NULL)
	{
		return ;
	}
	if (cmd->args != NULL)
	{
		while (cmd->args[i] != NULL)
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->redirect_lst != NULL)
		ft_lstclear(&cmd->redirect_lst, free_redirect);
	if (cmd->infile != NULL)
		free(cmd->infile);
	if (cmd->outfile != NULL)
		free(cmd->outfile);
	free(cmd);
}

void	free_cmd_list(t_cmd **cmd)
{
	t_cmd	*next;

	if (cmd == NULL || *cmd == NULL)
		return ;
	while (cmd != NULL && *cmd != NULL)
	{
		next = (*cmd)->next;
		free_cmd_node(*cmd);
		*cmd = next;
	}
	cmd = NULL;
	cmd = NULL;
}
