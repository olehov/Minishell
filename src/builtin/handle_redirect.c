/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:28:35 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/11 12:21:37 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_redirection.h"

static int	check_outfile_permission(t_cmd *cmd, char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		return (perror(filename), -1);
	}
	close(fd);
	ft_safe_free(cmd->outfile);
	cmd->outfile = ft_strdup(filename);
	return (0);
}

static int	check_infile_permission(t_cmd *cmd, char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags);
	if (fd < 0)
	{
		return (perror(filename), -1);
	}
	close(fd);
	ft_safe_free(cmd->infile);
	cmd->infile = ft_strdup(filename);
	return (0);
}

static int	redirect_loop(t_list *tmp, t_cmd *cmd,
	t_redirect_type *last_out_file)
{
	t_redirect		*redirect;

	redirect = (t_redirect *)tmp->content;
	if (redirect->type == _redirect_in || redirect->type == _heredoc)
	{
		if (check_infile_permission(cmd,
				redirect->filename, O_RDONLY) == -1)
			return (-1);
	}
	else if (redirect->type == _redirect_out)
	{
		if (check_outfile_permission(cmd,
				redirect->filename, O_CREAT | O_WRONLY | O_TRUNC) == -1)
			return (-1);
		*last_out_file = redirect->type;
	}
	else if (redirect->type == _append_to_file)
	{
		if (check_outfile_permission(cmd,
				redirect->filename, O_CREAT | O_WRONLY | O_APPEND) == -1)
			return (-1);
		*last_out_file = redirect->type;
	}
	return (0);
}

static int	redirect_fd(t_cmd *cmd, t_redirect_type last_out_file)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
			return (perror(cmd->infile), -1);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (last_out_file == _append_to_file)
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
			return (perror(cmd->outfile), -1);
		close(fd);
	}
	return (0);
}

int	handle_redirect(t_cmd *cmd)
{
	t_list			*tmp;
	t_redirect_type	last_out_file;

	tmp = cmd->redirect_lst;
	while (tmp)
	{
		if (redirect_loop(tmp, cmd, &last_out_file) == -1)
		{
			g_last_exit_code = EXIT_FAILURE;
			ft_safe_free(cmd->infile);
			ft_safe_free(cmd->outfile);
			return (-1);
		}
		tmp = tmp->next;
	}
	if (redirect_fd(cmd, last_out_file) == -1)
	{
		g_last_exit_code = EXIT_FAILURE;
		ft_safe_free(cmd->infile);
		ft_safe_free(cmd->outfile);
		return (-1);
	}
	return (0);
}
