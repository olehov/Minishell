/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:05:57 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/13 17:11:29 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	print_error(char *cmd, t_minish *msh)
{
	if (msh->exit_code == 0)
		return ;
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (msh->exit_code == 127)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else
		perror(cmd);
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

void	check_is_directory_permission(char **args, t_minish *msh)
{
	int	exist;

	if (args == NULL || args[0] == NULL
		|| (args[0][0] == '\0' && args[1] == NULL))
		exit(msh->exit_code);
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		exist = is_exists(args[0]);
		if (exist == -1)
			exit(EXIT_FAILURE);
		if (exist != 0)
			exit(exist);
	}
}

void	launch_child(t_cmd *cmd, t_minish *msh)
{
	char	*path;
	char	**envp;

	check_is_directory_permission(cmd->args, msh);
	set_pipe_fds(cmd, msh);
	close_all_pipes(msh->cmd);
	if (is_builtin(cmd->args))
	{
		execute_builtin(cmd, msh);
		exit(msh->exit_code);
	}
	path = find_executable_path(cmd->args[0], msh->env);
	envp = env_list_to_str_arr(msh->env);
	execve(path, cmd->args, envp);
	ft_safe_free(path);
	free_split(envp);
	msh->exit_code = 127;
	print_error(cmd->args[0], msh);
	exit(msh->exit_code);
}
