/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:50:42 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/17 14:15:26 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"

int	handle_word(char *input, int *i, char **accum, t_minish *msh)
{
	int		start;
	char	*part;

	(void)msh;
	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
		(*i)++;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '<'
		&& input[*i] != '>' && input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	part = ft_substr(input, start, *i - start);
	*accum = append_part(*accum, part);
	free(part);
	return (1);
}
