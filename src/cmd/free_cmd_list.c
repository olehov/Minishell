/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:01:48 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 14:02:47 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_cmd.h"
#include "../../include/ft_redirection.h"

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd != NULL)
	{
		tmp = cmd;
		i = 0;
		if (cmd->args != NULL)
		{
			while (cmd->args[i] != NULL)
				free(cmd->args[i++]);
			free(cmd->args);
		}
		if (cmd->redirect_lst != NULL)
			ft_lstclear(&cmd->redirect_lst, free_redirect);
		cmd = cmd->next;
		free(tmp);
	}
}
