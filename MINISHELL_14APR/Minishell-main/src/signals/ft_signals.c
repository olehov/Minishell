/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:09:02 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 15:12:45 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/ft_signals.h"

volatile sig_atomic_t	g_received_signal = 0;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_received_signal = SIGINT;
	}
}

void	child_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		exit(128 + SIGINT);
	}
	if (signo == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		exit(128 + SIGQUIT);
	}
}

void	heredoc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		exit(128 + SIGINT);
	}
}
