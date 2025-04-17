/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:50:07 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/17 19:46:00 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_shell(t_minish *msh)
{
	if (msh == NULL)
		return ;
	if (msh->heredocs != NULL)
		ft_lstclear(&msh->heredocs, free_heredoc);
	if (msh->cmd != NULL)
		free_cmd_list(&msh->cmd);
	if (msh->pipe_split != NULL)
		free_split(msh->pipe_split);
}

static int	minishell_loop(t_minish *msh)
{
	char	*line;

	line = get_line(msh);
	if (!line)
		return (-1);
	if (g_received_signal == SIGINT)
	{
		msh->exit_code = 128 + SIGINT;
		g_received_signal = 0;
	}
	if (*line)
		add_history(line);
	if (ft_syntax_error(line) == -1)
	{
		msh->exit_code = 2;
		return (free(line), 0);
	}
	msh->cmd = parse_input(line, msh->env, msh);
	free(line);
	if (msh->cmd == NULL)
		return (0);
	execute_commands(msh);
	unlink_heredocs(&msh->heredocs);
	reset_shell(msh);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minish	msh;
	int			exit_code;

	(void)argc;
	(void)argv;
	init_shell(&msh, envp);
	while (1)
	{
		set_signals();
		if (minishell_loop(&msh) == -1)
			break ;
	}
	rl_clear_history();
	exit_code = msh.exit_code;
	free_shell(&msh);
	exit(exit_code);
}
