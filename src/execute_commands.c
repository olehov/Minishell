/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:47:37 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/04 16:39:05 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "../include/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t	get_row_size(char **args)
{
	size_t	i;

	i = 0;
	if (args == NULL || *args == NULL)
	{
		return (0);
	}
	while (args[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	printerrcode(t_minish *msh)
{
	if (msh != NULL)
	{
		perror(ft_itoa(g_last_exit_code));
	}
}

// // --- Вбудовані команди ---
void	execute_builtin(t_cmd *cmd, t_minish *msh)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		if (get_row_size(cmd->args) > 2)
		{
			g_last_exit_code = 1;
			return (ft_putstr_fd(" too many arguments", STDERR_FILENO));
		}
		else if (ft_cd(cmd->args[1], &msh->env) == -1)
			g_last_exit_code = 1;
	}
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		if (printpwd() == -1)
			g_last_exit_code = 1;
	}
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		print_env_list(msh->env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		if (ft_set_env(&msh->env, cmd->args[1]) == -1)
			g_last_exit_code = 1;
	}
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_env_unset(&msh->env, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		if (get_row_size(cmd->args) > 2)
		{
			g_last_exit_code = 1;
			return (ft_putstr_fd(" too many arguments", STDERR_FILENO));
		}
		exit(0);
	}
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "$?") == 0)
		printerrcode(msh);
	g_last_exit_code = 0;
}

int	is_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "pwd") == 0
		|| ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "exit") == 0
		|| ft_strcmp(cmd[0], "$?") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "echo") == 0
		&& cmd[1] != NULL && ft_strcmp(cmd[1], "-n") == 0)
		return (1);
	return (0);
}

char *find_executable_path(char *cmd, t_list *env)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		return NULL;
	}

	char **paths = split_path(env, "PATH", ':');
	if (!paths)
		return NULL;

	char *full_path = NULL;
	for (int i = 0; paths[i]; i++)
	{
		char *tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);

		if (access(full_path, X_OK) == 0)
		{
			ft_free_2d_array(paths, -1);
			return full_path;
		}
		free(full_path);
	}
	ft_free_2d_array(paths, -1);
	return NULL;
}

static void close_all_pipes(t_cmd *cmd)
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
	if (cmd->next && dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
		exit(1);
	if (cmd->prev && dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
		exit(1);
}

static void handle_redirect(t_cmd *cmd)
{
	int fd;
	if (cmd->infile && ft_strcmp(cmd->infile, "<<") != 0
		&& (!cmd->args[1])) // тільки якщо немає додаткових аргументів
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror("Input file open failed");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append_out)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Output file open failed");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}


// void handle_redirect(t_cmd *cmd)
// {
// 	int fd;
// 	if (cmd->infile && ft_strcmp(cmd->infile, "<<") != 0)
// 	{
// 		fd = open(cmd->infile, O_RDONLY);
// 		if (fd < 0)
// 		{
// 			perror("Input file open failed");
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	if (cmd->outfile)
// 	{
// 		if (cmd->append_out)
// 			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		else
// 			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd < 0)
// 		{
// 			perror("Output file open failed");
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// }

static void launch_child(t_cmd *cmd, t_minish *msh)
{
	handle_redirect(cmd);
	if (cmd->infile && ft_strcmp(cmd->infile, "<<") == 0)
	{
		ft_heredoc(cmd->delimiter, msh->env);
		if (cmd->infile != NULL)
			free(cmd->infile);
		cmd->infile = ft_strdup(HEREDOC_FILENAME_PATH);
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
	g_last_exit_code = 127;
	exit(g_last_exit_code);
}

void execute_commands(t_minish *msh)
{
	t_cmd *cmd = msh->cmd;
	pid_t pid;

	while (cmd)
	{
		if (cmd->next && pipe(cmd->pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (!cmd->next && is_builtin(cmd->args))
		{
			execute_builtin(cmd, msh);
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			launch_child(cmd, msh);
		cmd->pid = pid;
		cmd = cmd->next;
	}
	close_all_pipes(msh->cmd);
	cmd = msh->cmd;
	while (cmd)
	{
		waitpid(cmd->pid, &g_last_exit_code, 0);
		if (WIFEXITED(g_last_exit_code))
			g_last_exit_code = WEXITSTATUS(g_last_exit_code);
		else if (WIFSIGNALED(g_last_exit_code))
			g_last_exit_code = 128 + WTERMSIG(g_last_exit_code);
		cmd = cmd->next;
	}
}
