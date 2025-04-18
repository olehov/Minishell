/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:50:42 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 03:42:07 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"

int	handle_word(char *input, int *i, char **accum, t_minish *msh)
{
	int		start;
	char	*part;
	char	quote;

	start = *i;
	quote = 0;
	if (input[*i] == '\'' || input[*i] == '\"')
		quote = input[(*i)++];
	if (quote)
	{
		while (input[*i] != '\0' && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*i)++;
	}
	else
	{
		while (input[*i] && !ft_isspace(input[*i])
			&& input[*i] != '<' && input[*i] != '>')
			(*i)++;
	}
	part = ft_substr(input, start, *i - start);
	*accum = append_part(*accum, part, msh);
	return (free(part), 1);
}
