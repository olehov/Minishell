/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_outside_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:11 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:43:02 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"

static void	ft_set_quote(char *quote, char value)
{
	if (!(*quote))
		*quote = value;
	else if (*quote == value)
		*quote = 0;
}

char	**split_outside_quotes(char *input, char delimiter)
{
	char	**result;
	int		i;
	int		j;
	int		start;
	char	quote;

	result = malloc(sizeof(char *) * (ft_strlen(input) / 2 + 2));
	i = -1;
	j = 0;
	start = 0;
	quote = 0;
	while (input[++i])
	{
		if ((input[i] == '\'' || input[i] == '\"'))
			ft_set_quote(&quote, input[i]);
		else if (input[i] == delimiter && !quote)
		{
			result[j++] = ft_substr(input, start, i - start);
			start = i + 1;
		}
	}
	if (i > start)
		result[j++] = ft_substr(input, start, i - start);
	result[j] = NULL;
	return (result);
}
