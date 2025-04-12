/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:42:55 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/11 12:43:34 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_all_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe_fd[0] > 0)
			close(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] > 0)
			close(cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
}

void	set_pipe_fds(t_cmd *cmd)
{
	if (cmd->next && cmd->outfile == NULL
		&& dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
		exit(g_last_exit_code);
	if (cmd->prev && cmd->infile == NULL
		&& dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
		exit(g_last_exit_code);
}
