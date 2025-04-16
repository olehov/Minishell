/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:05:57 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 20:02:57 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*find_executable_path(char *cmd, t_list *env)
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

static void	print_error_and_exit(char *cmd, t_minish *msh)
{
	int	exit_code;

	exit_code = 127;
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	clear_data(msh);
	exit(exit_code);
}

static int	is_exists(char *path)
{
	if (path == NULL)
		return (-1);
	if (ft_is_directory(path))
	{
		if (access(path, X_OK) == -1)
		{
			ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
			return (PERMISSION_DENIED);
		}
		ft_putstr_fd(" Is a directory\n", STDERR_FILENO);
		return (IS_A_DIRECTORY);
	}
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		return (PERMISSION_DENIED);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		return (126);
	}
	return (0);
}

static void	check_is_directory_permission(char **args, t_minish *msh)
{
	int	exist;

	if (args == NULL || args[0] == NULL
		|| (args[0][0] == '\0' && args[1] == NULL))
	{
		exist = msh->exit_code;
		clear_data(msh);
		exit(exist);
	}
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		exist = is_exists(args[0]);
		if (exist == -1)
		{
			clear_data(msh);
			exit(EXIT_FAILURE);
		}
		if (exist != 0)
		{
			clear_data(msh);
			exit(exist);
		}
	}
}

void	launch_child(t_cmd *cmd, t_minish *msh)
{
	char	*path;
	char	**envp;
	int		exit_code;

	check_is_directory_permission(cmd->args, msh);
	set_pipe_fds(cmd, msh);
	close_all_pipes(msh->cmd);
	if (is_builtin(cmd->args))
	{
		execute_builtin(cmd, msh);
		exit_code = msh->exit_code;
		clear_data(msh);
		exit(exit_code);
	}
	path = find_executable_path(cmd->args[0], msh->env);
	if (path == NULL)
		print_error_and_exit(cmd->args[0], msh);
	envp = env_list_to_str_arr(msh->env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->args, envp);
	free(path);
	free_split(envp);
	print_error_and_exit(cmd->args[0], msh);
}
