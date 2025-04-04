/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:30:58 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/04 10:40:57 by ogrativ          ###   ########.fr       */
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
	int		i = 0, j = 0;
	char	quote = 0;
	char	*res = malloc(ft_strlen(str) + 1);
	if (!res) return NULL;

	while (str[i])
	{
		if (!quote && ft_is_quote(str[i])
			&& is_closed_quote(str[i], i + 1, str))
		{
			quote = str[i++];
			continue ;
		}
		else if (quote && str[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}


// char	*remove_quotes(char *str)
// {
// 	int		i = 0, j = 0;
// 	char	quote = 0;
// 	char	*res = malloc(ft_strlen(str) + 1);
// 	if (!res) return NULL;

// 	while (str[i])
// 	{
// 		if (!quote && (str[i] == '\'' || str[i] == '"'))
// 		{
// 			quote = str[i]; // відкрилась лапка
// 			i++; // пропускаємо відкриваючу
// 		}
// 		else if (quote && str[i] == quote)
// 		{
// 			quote = 0; // закрилась лапка
// 			i++; // пропускаємо закриваючу
// 		}
// 		else
// 			res[j++] = str[i++];
// 	}
// 	res[j] = '\0';
// 	return (res);
// }


// char	*remove_quotes(char *str)
// {
// 	int		i = 0, j = 0;
// 	char	quote = 0;
// 	char	*res = malloc(ft_strlen(str) + 1);

// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (!quote && (str[i] == '\'' || str[i] == '\"'))
// 		{
// 			if (is_closed_quote(str[i], i + 1, str))
// 			{
// 				quote = str[i];
// 				i++;
// 				continue ;
// 			}
// 		}
// 		else if (quote && str[i] == quote)
// 		{
// 			quote = 0;
// 			i++;
// 			continue ;
// 		}
// 		res[j++] = str[i++];
// 	}
// 	res[j] = '\0';
// 	return (res);
// }


// ===== Додавання аргументу в масив =====
void add_arg(t_cmd *cmd, char *arg)
{
	int i = 0;
	char **new_args;

	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		cmd->args[0] = arg;
		cmd->args[1] = NULL;
		return ;
	}
	while (cmd->args[i]) i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	for (int j = 0; j < i; j++) new_args[j] = cmd->args[j];
	new_args[i] = arg;
	new_args[i + 1] = NULL;
	if (cmd->args != NULL)
		free(cmd->args);
	cmd->args = new_args;
}

// ===== Обробка редіректів для команди =====
void	handle_redirects(t_cmd *cmd)
{
	if (cmd->outfile)
	{
		if (cmd->append_out)
			append_to_file(cmd->infile, cmd->outfile, O_RDWR | O_APPEND);
		else
			append_to_file(cmd->infile, cmd->outfile, O_RDWR | O_TRUNC);
	}
	if (cmd->infile)
	{
		if (cmd->redirect_in)
		{
			append_to_file(cmd->outfile, cmd->infile,
				O_RDONLY | O_CREAT | O_TRUNC);
		}
	}
}

// ===== Перевірка для echo -n (чи лише n) =====
int only_n(char *str)
{
	int i = 1;
	if (str[0] != '-') return 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}
