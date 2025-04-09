/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:05:11 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 20:27:28 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_heredoc.h"

static bool	check_delimiter(const char *delimiter)
{
	if (delimiter == NULL)
	{
		errno = EINVAL;
		return (perror("delimiter can't be NULL"), false);
	}
	return (true);
}

char	*get_delimiter_without_quotes(char *delimiter, bool *in_quotes)
{
	char	*tmp;
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (check_delimiter(delimiter) == 0)
		return (NULL);
	tmp = ft_calloc(sizeof(char *), ft_strlen(delimiter));
	if (tmp == NULL)
		return (perror("Can't allocate memory"), NULL);
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

static int	read_line(int fd, char *delimiter, t_list *env, bool in_quotes)
{
	char	*buffer;
	char	*tmp;

	if (isatty(STDIN_FILENO))
		buffer = readline("> ");
	else
		buffer = readline(NULL);
	if (buffer == NULL)
	{
		return (0);
	}
	if (ft_strcmp(buffer, delimiter) == 0)
	{
		return (free(buffer), 0);
	}
	if (in_quotes == false)
	{
		tmp = process_env(buffer, env);
		ft_putendl_fd(tmp, fd);
		free(tmp);
	}
	else
		ft_putendl_fd(buffer, fd);
	free(buffer);
	return (1);
}

int	ft_heredoc(t_heredoc *heredoc, t_list *env)
{
	int		fd;
	int		exit_status;
	bool	in_quotes;
	char	*del_without_quotes;

	in_quotes = false;
	exit_status = 1;
	if (check_delimiter(heredoc->delimiter) == 0)
		return (-1);
	fd = open(heredoc->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	del_without_quotes = get_delimiter_without_quotes(heredoc->delimiter,
			&in_quotes);
	while (exit_status != -1 && exit_status != 0)
		exit_status = read_line(fd, del_without_quotes, env, in_quotes);
	close(fd);
	if (in_quotes == true)
		free(del_without_quotes);
	return (0);
}
