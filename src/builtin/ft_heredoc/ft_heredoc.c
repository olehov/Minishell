/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:05:11 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:53:03 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_heredoc.h"

static char	*allocate_delimitter(char *delimiter)
{
	char	*tmp;

	if (check_delimiter(delimiter) == 0)
		return (NULL);
	tmp = ft_calloc(sizeof(char), ft_strlen(delimiter) + 1);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

static char	*get_delimiter_without_quotes(char *delimiter, bool *in_quotes)
{
	char	*tmp;
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = allocate_delimitter(delimiter);
	if (tmp == NULL)
		return (NULL);
	while (delimiter[i] != '\0')
	{
		if (delimiter[i] == '\'' || delimiter[i] == '\"')
		{
			*in_quotes = true;
			quote = delimiter[i++];
			while (delimiter[i] != quote && delimiter[i] != '\0')
				tmp[j++] = delimiter[i++];
		}
		else
			tmp[j++] = delimiter[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

static void	print_err(char *delimiter)
{
	ft_putstr_fd(" here-document delimited by end-of-file ",
		STDERR_FILENO);
	ft_putstr_fd("(wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}

static int	read_line(int fd, char *delimiter,
	t_minish *msh, bool in_quotes)
{
	char	*buffer;
	char	*tmp;

	msh->exit_code = 0;
	if (isatty(STDIN_FILENO))
		buffer = readline("> ");
	else
		buffer = readline(NULL);
	if (g_received_signal == SIGINT)
		return (free(buffer), -1);
	if (buffer == NULL)
		return (print_err(delimiter), 0);
	if (ft_strcmp(buffer, delimiter) == 0)
		return (free(buffer), 0);
	if (in_quotes == false)
	{
		tmp = process_env(buffer, msh->env, msh);
		ft_putendl_fd(tmp, fd);
		free(tmp);
	}
	else
		ft_putendl_fd(buffer, fd);
	free(buffer);
	return (1);
}

int	ft_heredoc(t_heredoc *heredoc, t_minish *msh)
{
	int		fd;
	int		exit_status;
	bool	in_quotes;
	char	*del_without_quotes;

	in_quotes = false;
	exit_status = 1;
	if (get_delimiter(heredoc) == -1)
		return (-1);
	if (g_received_signal == SIGINT)
		return (-1);
	if (check_delimiter(heredoc->delimiter) == 0)
		return (-1);
	fd = open(heredoc->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	del_without_quotes = get_delimiter_without_quotes(heredoc->delimiter,
			&in_quotes);
	while (exit_status != -1 && exit_status != 0)
		exit_status = read_line(fd, del_without_quotes, msh, in_quotes);
	close(fd);
	free(del_without_quotes);
	if (exit_status == -1)
		return (-1);
	return (0);
}
