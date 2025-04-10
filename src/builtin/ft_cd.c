/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:11:06 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 20:06:23 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <linux/limits.h>
#include <dirent.h>

static int	cd_error_handler(int cd_out)
{
	if (cd_out != -1)
		return (cd_out);
	if (errno == EACCES)
		return (perror("Can't accest to component of path"), cd_out);
	if (errno == EFAULT)
		return (perror("Path outside accessible address space"), cd_out);
	if (errno == ENOENT)
		return (perror("Directory does not exist"), cd_out);
	if (errno == ENOTDIR)
		return (perror("A component of path is not a directory"), cd_out);
	if (errno == ENAMETOOLONG)
		return (perror("Path is to long:"), cd_out);
	if (errno == EIO)
		return (ft_putstr_fd("An I/O error occurred", STDERR_FILENO), cd_out);
	if (errno == ENOMEM)
		return (perror("Insufficient kernel memory was available"), cd_out);
	if (errno == ELOOP)
	{
		ft_putstr("Too many symbolic links were encountered in resolving path",
			STDERR_FILENO);
		return (cd_out);
	}
	return (cd_out);
}

int	is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}


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

void	print_cd_error(void)
{
	if (errno == ENOENT)
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd(" Permision denied\n", STDERR_FILENO);
	else if (errno == ENOTDIR)
		ft_putstr_fd(" Not a directory\n", STDERR_FILENO);
}

static int	ft_chdir(char *path, t_list **lst)
{
	char	old_path[PATH_MAX];

	if (getcwd(old_path, PATH_MAX) == NULL)
		return (-1);
	if (!is_directory(path))
	{
		errno = ENOTDIR;
		return (print_cd_error(), -1);
	}
	if (chdir(path) == 0)
	{
		print_cd_error();
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
		return (cd_error_handler(ft_chdir(env->value, lst)));
	if (path != NULL)
	{
		while (*path != '/')
			path++;
		path2 = ft_strjoin(env->value, path);
		if (path2 == NULL)
			return (-1);
		return_val = cd_error_handler(ft_chdir(path2, lst));
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
		return (print_cd_error(), -1);
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
		return (ft_chdir(env->value, lst));
	}
	return (ft_chdir(path, lst));
}
