/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:50:07 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:50:49 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	minishell_loop(t_minish *msh)
{
	char	*line;

	line = get_line(msh);
	if (!line)
	{
		msh->exit_code = 0;
		return (-1);
	char	*line;

	line = get_line(msh);
	if (!line)
	{
		msh->exit_code = 0;
		return (-1);
	}
	if (g_received_signal == SIGINT)
	{
		msh->exit_code = 128 + SIGINT;
		g_received_signal = 0;
	}
	if (g_received_signal == SIGINT)
	{
		msh->exit_code = 128 + SIGINT;
		g_received_signal = 0;
	}
	if (*line)
		add_history(line);
	msh->cmd = parse_input(line, msh->env, msh);
	msh->cmd = parse_input(line, msh->env, msh);
	free(line);
	if (msh->cmd == NULL)
		return (0);
	execute_commands(msh);
	free_cmd_list(&msh->cmd);
	unlink_heredocs(&msh->heredocs);
	return (0);
}

	if (msh->cmd == NULL)
		return (0);
	execute_commands(msh);
	free_cmd_list(&msh->cmd);
	unlink_heredocs(&msh->heredocs);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minish	msh;
	int			exit_code;
	int			exit_code;

	(void)argc;
	(void)argv;
	init_shell(&msh, envp);
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
	exit_code = msh.exit_code;
	free_shell(&msh);
	exit(exit_code);
}
