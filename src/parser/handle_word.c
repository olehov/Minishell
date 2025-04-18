/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:50:42 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 01:47:04 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"

int	handle_word(char *input, int *i, char **accum, t_minish *msh)
{
	int		start;
	char	*part;
	char	current_quote;

	(void)msh;
	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '|' && input[*i] != '&' && input[*i] != ';')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			current_quote = input[*i];
			(*i)++; // пропускаємо відкриту лапку
			start = *i;
			while (input[*i] && input[*i] != current_quote)
				(*i)++;
			if (*i > start) // якщо щось всередині лапок є
			{
				part = ft_substr(input, start, *i - start);
				*accum = append_part(*accum, part);
				free(part);
			}
			if (input[*i] == current_quote)
				(*i)++; // пропускаємо закриту лапку
		}
		else
		{
			start = *i;
			while (input[*i] && !ft_isspace(input[*i])
				&& input[*i] != '<' && input[*i] != '>'
				&& input[*i] != '|' && input[*i] != '&' && input[*i] != ';'
				&& input[*i] != '\'' && input[*i] != '"')
				(*i)++;
			if (*i > start)
			{
				part = ft_substr(input, start, *i - start);
				*accum = append_part(*accum, part);
				free(part);
			}
		}
	}
	return (1);
}


// int	handle_word(char *input, int *i, char **accum, t_minish *msh)
// {
// 	int		start;
// 	char	*part;
// 	char	current_quote;

// 	(void)msh;
// 	start = *i;
// 	while (input[*i])
// 	{
// 		if (ft_isspace(input[*i])
// 			|| input[*i] == '<' || input[*i] == '>'
// 			|| input[*i] == '|' || input[*i] == '&'
// 			|| input[*i] == ';')
// 			break;
// 		else if (input[*i] == '\'' || input[*i] == '"')
// 		{
// 			current_quote = input[*i];
// 			(*i)++;
// 			while (input[*i] && input[*i] != current_quote)
// 				(*i)++;
// 			if (input[*i] == current_quote)
// 				(*i)++;
// 		}
// 		else
// 			(*i)++;
// 	}
// 	part = ft_substr(input, start, *i - start);
// 	*accum = append_part(*accum, part);
// 	free(part);
// 	return (1);
// }


// int	handle_word(char *input, int *i, char **accum, t_minish *msh)
// {
// 	int		start;
// 	char	*part;
// 	char	current_quote;

// 	(void)msh;
// 	start = *i;
// 	while (input[*i])
// 	{
// 		if (ft_isspace(input[*i]) || input[*i] == '<' || input[*i] == '>'
// 			|| input[*i] == '|')
// 			break ;
// 		if (input[*i] == '\'' || input[*i] == '"')
// 		{
// 			current_quote = input[(*i)++];
// 			while (input[*i] && input[*i] != current_quote)
// 				(*i)++;
// 			if (input[*i] == current_quote)
// 				(*i)++;
// 		}
// 		else
// 			(*i)++;
// 	}
// 	part = ft_substr(input, start, *i - start);
// 	*accum = append_part(*accum, part);
// 	free(part);
// 	return (1);
// }




// int	handle_word(char *input, int *i, char **accum, t_minish *msh)
// {
// 	int		start;
// 	char	*part;
// 	char	quote;

// 	(void)msh;
// 	start = *i;
// 	quote = 0;
// 	if (input[*i] == '\'' || input[*i] == '"')
// 		quote = input[(*i)++];
// 	if (quote)
// 	{
// 		while (input[*i] && input[*i] != quote)
// 			(*i)++;
// 		if (input[*i] == quote)
// 			(*i)++;
// 	}
// 	else
// 	{
// 		while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '<'
// 			&& input[*i] != '>' && input[*i] != '\'' && input[*i] != '"')
// 			(*i)++;
// 	}
// 	part = ft_substr(input, start, *i - start);
// 	*accum = append_part(*accum, part);
// 	free(part);
// 	return (1);
// }
