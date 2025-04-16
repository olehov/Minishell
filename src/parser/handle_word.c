/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:50:42 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:12:20 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_parser.h"

int	handle_word(char *input, int *i, char **accum, t_minish *msh)
{
	int		start;
	char	*part;
	char	*tmp;

	start = *i;
	if (input[*i] == '\'' || input[*i] == '\"')
		(*i)++;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '<'
		&& input[*i] != '>' && input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	part = ft_substr(input, start, *i - start);
	tmp = process_env(part, msh->env, msh);
	*accum = append_part(*accum, tmp);
	free(part);
	free(tmp);
	return (1);
}
