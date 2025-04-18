/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:04 by mfedorys          #+#    #+#             */
/*   Updated: 2025/04/18 06:26:18 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"
#include <fcntl.h>
#include <unistd.h>

static bool	check_start(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		return (print_syntax_err(&input[i]), true);
	return (false);
}

static void	skip_quotes(char *input, int *i)
{
	char	quote;

	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i])
		(*i)++;
}

static bool	check_pipe(char *input, int *i)
{
	(*i)++;
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (input[*i] == '|' || input[*i] == '\0'
		|| input[*i] == '<' || input[*i] == '>')
		return (print_syntax_err(&input[*i]), true);
	return (false);
}

static bool	check_redirect(char *input, int *i)
{
	char	c;

	c = input[*i];
	(*i)++;
	if (input[*i] == c)
		(*i)++;
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (input[*i] == '\0' || input[*i] == '|'
		|| input[*i] == '>' || input[*i] == '<')
		return (print_syntax_err(&input[*i]), true);
	return (false);
}

int	ft_syntax_error(char *input)
{
	int	i;

	i = 0;
	if (check_start(input))
		return (1);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			skip_quotes(input, &i);
		else if (input[i] == '|')
		{
			if (check_pipe(input, &i))
				return (1);
		}
		else if (input[i] == '>' || input[i] == '<')
		{
			if (check_redirect(input, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
