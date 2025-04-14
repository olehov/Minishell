/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:30:58 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 14:52:44 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_closed_quote(char quote, int start, char *str)
{
	const char	single_quote = '\'';
	const char	double_quote = '\"';

	if (str == NULL || quote == 0)
		return (false);
	while (str[start] != '\0')
	{
		if (str[start] == single_quote || str[start] == double_quote)
		{
			if ((str[start] == single_quote && quote == single_quote)
				|| (str[start] == double_quote && quote == double_quote))
				return (true);
			else
				return (false);
		}
		start++;
	}
	return (false);
}

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/*removing quotes from line*/

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (!quote && ft_is_quote(str[i])
			&& is_closed_quote(str[i], i + 1, str))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

// ===== adding arguments to array =====
void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0;
	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		cmd->args[0] = arg;
		cmd->args[1] = NULL;
		return ;
	}
	while (cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	while (j < i)
	{
		new_args[j] = cmd->args[j];
		j++;
	}
	new_args[i] = arg;
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}
