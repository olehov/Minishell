/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:47:37 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/11 14:51:43 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "../include/minishell.h"
#include "../include/ft_redirection.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>

void	reset_std_fds(int std_fd[2])
{
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	close(std_fd[0]);
	close(std_fd[1]);
}

int	run_single_cmd(t_cmd *cmd, t_minish *msh)
{
	int		std_fd[2];

	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (cmd && !cmd->next && cmd->args != NULL && is_builtin(cmd->args))
	{
		if (handle_redirect(cmd) == -1)
		{
			return (-1);
		}
		execute_builtin(cmd, msh);
		return (reset_std_fds(std_fd), 0);
	}
	return (1);
}

void	run_child(t_cmd *cmd, t_minish *msh, pid_t pid)
{
	if (pid == -1)
	{
		g_last_exit_code = EXIT_FAILURE;
		exit(g_last_exit_code);
	}
	if (pid == 0)
	{
		g_last_exit_code = 0;
		if (handle_redirect(cmd) == -1)
		{
			cmd = cmd->next;
			if (g_last_exit_code != 0)
				exit(g_last_exit_code);
		}
		launch_child(cmd, msh);
	}
	cmd->pid = pid;
}

void	wait_all_proccesses(t_minish *msh)
{
	t_cmd	*cmd;
	int		status;
	int		last_status;

	cmd = msh->cmd;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (cmd->next == NULL)
			last_status = ft_decode_wstatus(status);
		cmd = cmd->next;
	}
	g_last_exit_code = last_status;
}

void	execute_commands(t_minish *msh)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = msh->cmd;
	if (run_single_cmd(cmd, msh) != 1)
		return ;
	while (cmd)
	{
		if (cmd->args == NULL)
		{
			g_last_exit_code = 0;
			cmd = cmd->next;
			continue ;
		}
		if (cmd->next && pipe(cmd->pipe_fd) == -1)
		{
			ft_putstr_fd(" Broken pipe\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		run_child(cmd, msh, pid);
		cmd = cmd->next;
	}
	close_all_pipes(msh->cmd);
	wait_all_proccesses(msh);
}
