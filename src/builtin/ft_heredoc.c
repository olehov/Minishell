/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:05:11 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 14:56:22 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_heredoc.h"

static char	*get_new_delimiter(char *delimiter, char quote)
{
	char	*tmp;
	char	*old_str;
	char	*new_str;

	tmp = readline("> ");
	if (tmp == NULL)
	{
		ft_putstr_fd(" unexpected EOF while looking for matching `",
			STDERR_FILENO);
		ft_putchar_fd(quote, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (NULL);
	}
	old_str = ft_strdup(delimiter);
	new_str = ft_strjoin3(old_str, "\n", tmp);
	free(old_str);
	free(tmp);
	return (new_str);
}

static void	set_closed_quote(t_heredoc *heredoc,
	char *quote, bool *is_closed_quote)
{
	size_t	i;

	while (heredoc->delimiter[i] != '\0')
	{
		while (heredoc->delimiter[i] != '\'' && heredoc->delimiter[i] != '\"'
			&& heredoc->delimiter[i] != '\0')
			i++;
		if (heredoc->delimiter[i] == '\'' || heredoc->delimiter[i] == '\"')
		{
			*quote = heredoc->delimiter[i++];
			*is_closed_quote = false;
		}
		while (heredoc->delimiter[i] != *quote && heredoc->delimiter[i] != '\0')
			i++;
		if (heredoc->delimiter[i] == '\'' || heredoc->delimiter[i] == '\"')
		{
			*quote = 0;
			*is_closed_quote = true;
			i++;
		}
	}
}

static void	get_delimiter(t_heredoc *heredoc)
{
	char	quote;
	bool	is_closed_quote;
	char	*delimiter;

	quote = 0;
	is_closed_quote = true;
	if (heredoc->delimiter == NULL)
		return ;
	set_closed_quote(heredoc, &quote, &is_closed_quote);
	if (!is_closed_quote)
	{
		delimiter = ft_strdup(heredoc->delimiter);
		free(heredoc->delimiter);
		heredoc->delimiter = get_new_delimiter(delimiter, quote);
		free(delimiter);
		if (heredoc->delimiter == NULL)
			return ;
		get_delimiter(heredoc);
	}
}

static bool	check_delimiter(const char *delimiter)
{
	if (delimiter == NULL)
	{
		errno = EINVAL;
		ft_putendl_fd(" unexpected end of file", STDERR_FILENO);
		return (false);
	}
	if (delimiter[0] == '\0')
	{
		errno = EINVAL;
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}

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

char	*get_delimiter_without_quotes(char *delimiter, bool *in_quotes)
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

	if (isatty(STDIN_FILENO))
		buffer = readline("> ");
	else
		buffer = readline(NULL);
	if (buffer == NULL)
	{
		print_err(delimiter);
		return (-1);
	}
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
	get_delimiter(heredoc);
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
	return (0);
}
