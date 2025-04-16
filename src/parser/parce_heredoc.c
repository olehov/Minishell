/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:20 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 15:13:02 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"
// #include "../../include/minishell.h"

static void	launch_heredoc_child(t_minish *msh, t_cmd *cmd,
	t_heredoc *heredoc)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		set_heredoc_signals();
		status = ft_heredoc(heredoc, msh);
		free_cmd_node(cmd);
		free_tokens(msh->tokens);
		free_heredoc(heredoc);
		clear_data(msh);
		if (g_received_signal == SIGINT)
			exit(128 + SIGINT);
		if (status == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	msh->exit_code = ft_decode_wstatus(status);
}

int	parce_heredoc(t_minish *msh, int *i, t_cmd *cmd)
{
	t_heredoc	*heredoc;
	char		*delimiter;

	delimiter = remove_outer_quotes(msh->tokens[++(*i)].value);
	heredoc = init_heredoc(delimiter);
	free(delimiter);
	if (heredoc == NULL)
	{
		msh->exit_code = 1;
		return (1);
	}
	launch_heredoc_child(msh, cmd, heredoc);
	set_signals();
	if (msh->exit_code == (128 + SIGINT))
		return (free_heredoc(heredoc), -1);
	add_redirection(cmd, _heredoc, heredoc->filename);
	if (msh->heredocs == NULL)
		msh->heredocs = ft_lstnew(heredoc);
	else
		ft_lstadd_back(&msh->heredocs, ft_lstnew(heredoc));
	return (0);
}
