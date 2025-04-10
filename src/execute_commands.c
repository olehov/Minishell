/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:47:37 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/10 17:16:07 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "../include/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>

void	printerrcode(t_minish *msh)
{
	char	*exit_code;

	exit_code = ft_itoa(g_last_exit_code);
	if (msh != NULL && exit_code != NULL)
	{
		perror(exit_code);
	}
	free(exit_code);
}

int	run_cd(t_cmd *cmd, t_minish *msh)
{
	if (get_row_size(cmd->args) > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	else
		return (ft_cd(cmd->args[1], &msh->env));
}

// // --- Вбудовані команди ---
void	execute_builtin(t_cmd *cmd, t_minish *msh)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		exit_code = run_cd(cmd, msh);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exit_code = printpwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		print_env_list(msh->env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		exit_code = ft_set_env(&msh->env, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_env_unset(&msh->env, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit(g_last_exit_code);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		exit_code = ft_echo(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "$?") == 0)
		printerrcode(msh);
	if (exit_code == -1)
		g_last_exit_code = EXIT_FAILURE;
	else
		g_last_exit_code = EXIT_SUCCESS;
}

char	*find_executable_path(char *cmd, t_list *env)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = split_path(env, "PATH", ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
	}
	return (free_split(paths), NULL);
}

static void	close_all_pipes(t_cmd *cmd)
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

static void	set_pipe_fds(t_cmd *cmd)
{
	if (cmd->next && cmd->outfile == NULL
		&& dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
		exit(g_last_exit_code);
	if (cmd->prev && cmd->infile == NULL
		&& dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
		exit(g_last_exit_code);
}

bool	check_access(char *filename, int flags)
{
	if (access (filename, F_OK) == 0 && access(filename, flags) == -1)
	{
		g_last_exit_code = 1;
		ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int handle_redirect(t_cmd *cmd)
{
	t_list			*tmp;
	t_redirect		*redirect;
	int				fd;
	t_redirect_type	last_out_file;

	tmp = cmd->redirect_lst;
	while (tmp)
	{
		redirect = (t_redirect *)tmp->content;
		if (redirect->type == _redirect_in || redirect->type == _heredoc)
		{
			fd = open(redirect->filename, O_RDONLY);
			if (fd < 0)
			{
				g_last_exit_code = 1;
				return (perror(redirect->filename), -1);
			}
			close(fd);
			if (cmd->infile != NULL)
				free(cmd->infile);
			cmd->infile = ft_strdup(redirect->filename);
		}
		else if (redirect->type == _redirect_out)
		{
			fd = open(redirect->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				g_last_exit_code = 1;
				return (perror(redirect->filename), -1);
			}
			close(fd);
			if (cmd->outfile != NULL)
				free(cmd->outfile);
			cmd->outfile = ft_strdup(redirect->filename);
			last_out_file = redirect->type;
		}
		else if (redirect->type == _append_to_file)
		{
			fd = open(redirect->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				g_last_exit_code = 1;
				return (perror(redirect->filename), -1);
			}
			close(fd);
			if (cmd->outfile != NULL)
				free(cmd->outfile);
			cmd->outfile = ft_strdup(redirect->filename);
			last_out_file = redirect->type;
		}
		tmp = tmp->next;
	}
	if (cmd->infile)
	{
		fd = open(redirect->filename, O_RDONLY);
		if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
		{
			g_last_exit_code = 1;
			return (perror(redirect->filename), -1);
		}
		close(fd);
	}
	if (cmd->outfile)
	{
		if (last_out_file == _append_to_file)
			fd = open(redirect->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(redirect->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
		{
			g_last_exit_code = 1;
			return (perror(redirect->filename), -1);
		}
		close(fd);
	}
	return (0);
}

void	print_error(char *cmd)
{
	if (g_last_exit_code == 0)
		return ;
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (g_last_exit_code == 127)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else
		perror(cmd);
}

static void launch_child(t_cmd *cmd, t_minish *msh)
{
	if (cmd->args == NULL || cmd->args[0] == NULL
		|| (cmd->args[0][0] == '\0' && cmd->args[1] == NULL))
		exit(g_last_exit_code);
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (ft_is_directory(cmd->args[0]))
		{
			if (access(cmd->args[0], X_OK) == -1)
			{
				g_last_exit_code = 127;
				ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
				exit(g_last_exit_code);
			}
			g_last_exit_code = 126;
			ft_putstr_fd(" Is a directory\n", STDERR_FILENO);
			exit(g_last_exit_code);
		}
		if (access(cmd->args[0], F_OK) == -1)
		{
			g_last_exit_code = 127;
			ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
			exit(g_last_exit_code);
		}
		if (access(cmd->args[0], X_OK) == -1)
		{
			g_last_exit_code = 126;
			ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
			exit(g_last_exit_code);
		}
	}
	set_pipe_fds(cmd);
	close_all_pipes(msh->cmd);
	if (is_builtin(cmd->args))
	{
		execute_builtin(cmd, msh);
		exit(g_last_exit_code);
	}
	char *path = find_executable_path(cmd->args[0], msh->env);
	char **envp = env_list_to_str_arr(msh->env);
	execve(path, cmd->args, envp);
	free(path);
	free_split(envp);
	g_last_exit_code = 127;
	print_error(cmd->args[0]);
	exit(g_last_exit_code);
}

void execute_commands(t_minish *msh)
{
	t_cmd *cmd = msh->cmd;
	pid_t pid;
	int		status;
	int		last_status;
	int		std_fd[2];

	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);

	if (cmd && !cmd->next && cmd->args != NULL && is_builtin(cmd->args))
	{
		if (handle_redirect(cmd) == -1)
		{
			if (g_last_exit_code != 0)
				return ;
		}
		execute_builtin(cmd, msh);
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
		close(std_fd[0]);
		close(std_fd[1]);
		return ;
	}
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
		if (pid == -1)
		{
			g_last_exit_code = EXIT_FAILURE;
			perror("fork");
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
		cmd = cmd->next;
	}
	close_all_pipes(msh->cmd);
	cmd = msh->cmd;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (cmd->next == NULL)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		cmd = cmd->next;
	}
	g_last_exit_code = last_status;
}
