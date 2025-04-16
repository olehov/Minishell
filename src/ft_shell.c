/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:14:40 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:50:27 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_minish *msh, char **envp)
{
	msh->env = NULL;
	msh->heredocs = NULL;
	msh->cmd = NULL;
	msh->pipe_split = NULL;
	msh->tokens = NULL;
	msh->exit_code = 0;
	if (init_env(&msh->env, envp) == -1)
	{
		msh->exit_code = EXIT_FAILURE;
		ft_putstr_fd("Failed to initialize environment\n", STDERR_FILENO);
		exit(msh->exit_code);
	}
}

void	free_shell(t_minish *msh)
{
	if (msh == NULL)
		return ;
	if (msh->env)
		ft_lstclear(&msh->env, free_env);
	if (msh->heredocs)
		ft_lstclear(&msh->heredocs, free_heredoc);
	if (msh->cmd != NULL)
		free_cmd_list(&msh->cmd);
	if (msh->pipe_split != NULL)
		free_split(msh->pipe_split);
	msh->exit_code = 0;
}
