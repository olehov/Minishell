/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:11:06 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/10 14:30:48 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <linux/limits.h>

void	change_path(t_list **lst, char *old_path)
{
	t_env	*env;
	char	buf[PATH_MAX];

	env = ft_get_env(*lst, "OLDPWD");
	if (env != NULL)
	{
		free(env->value);
		env->value = ft_strdup(old_path);
	}
	env = ft_get_env(*lst, "PWD");
	if (env != NULL)
	{
		free(env->value);
		if (getcwd(buf, PATH_MAX) == NULL)
			return ;
		env->value = ft_strdup(buf);
	}
}

static int	print_cd_error(int cd_out)
{
	if (cd_out != -1)
		return (cd_out);
	if (errno == ENOENT)
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd(" Permision denied\n", STDERR_FILENO);
	else if (errno == ENOTDIR)
		ft_putstr_fd(" Not a directory\n", STDERR_FILENO);
	return (cd_out);
}

static int	ft_chdir(char *path, t_list **lst)
{
	char	old_path[PATH_MAX];

	if (getcwd(old_path, PATH_MAX) == NULL)
		return (-1);
	if (!ft_is_directory(path))
	{
		errno = ENOTDIR;
		return (print_cd_error(-1));
	}
	if (chdir(path) == 0)
	{
		return (change_path(lst, old_path), 0);
	}
	return (-1);
}

static int	ft_cd_home(char *path, t_list **lst)
{
	t_env	*env;
	char	*path2;
	int		return_val;

	env = ft_get_env(*lst, "HOME");
	if (env == NULL)
		return (-1);
	if (path == NULL || ft_strcmp(path, "~") == 0)
		return (print_cd_error(ft_chdir(env->value, lst)));
	if (path != NULL)
	{
		while (*path != '/')
			path++;
		path2 = ft_strjoin(env->value, path);
		if (path2 == NULL)
			return (-1);
		return_val = print_cd_error(ft_chdir(path2, lst));
		free(path2);
		return (return_val);
	}
	return (-1);
}

int	ft_cd(char *path, t_list **lst)
{
	t_env	*env;
	char	oldpwd[PATH_MAX];

	if (*lst == NULL)
		return (-1);
	if (access(path, F_OK) != 0)
	{
		errno = ENOENT;
		return (print_cd_error(-1));
	}
	if (ft_get_env(*lst, "OLDPWD") == NULL)
		ft_set_env(lst, ft_strjoin("OLDPWD=", getcwd(oldpwd, PATH_MAX)));
	if (path == NULL || path[0] == '~')
		return (ft_cd_home(path, lst));
	if (ft_strcmp(path, "-") == 0)
	{
		env = ft_get_env(*lst, "OLDPWD");
		if (env == NULL)
			return (-1);
		return (print_cd_error(ft_chdir(env->value, lst)));
	}
	return (print_cd_error(ft_chdir(path, lst)));
}
