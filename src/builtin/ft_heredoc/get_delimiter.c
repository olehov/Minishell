/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:17:20 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/15 13:17:15 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_heredoc.h"

static char	*get_new_delimiter(char *delimiter, char quote)
{
	char	*tmp;
	char	*old_str;
	char	*new_str;

	tmp = readline("> ");
	if (g_received_signal == SIGINT)
		return (free(tmp), NULL);
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

	i = 0;
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

int	get_delimiter(t_heredoc *heredoc)
{
	char	quote;
	bool	is_closed_quote;
	char	*delimiter;

	quote = 0;
	is_closed_quote = true;
	if (heredoc->delimiter == NULL)
		return (-1);
	set_closed_quote(heredoc, &quote, &is_closed_quote);
	if (!is_closed_quote)
	{
		delimiter = ft_strdup(heredoc->delimiter);
		free(heredoc->delimiter);
		heredoc->delimiter = get_new_delimiter(delimiter, quote);
		free(delimiter);
		if (g_received_signal == SIGINT)
			return (1);
		if (heredoc->delimiter == NULL)
			return (-1);
		get_delimiter(heredoc);
	}
	return (0);
}
