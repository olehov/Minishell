/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_quoted_text.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:30:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:37:50 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_env.h"
#include "../../include/process_env_utils.h"

static int	process_quoted_text_loop(const char *input,
	int *i, t_env_state *state, t_minish *msh)
{
	if (state->quote == '\'' && input[*i])
	{
		if (try_ensure_buffer_capacity(state, 1, input[*i]) == -1)
			return (-1);
		(*i)++;
	}
	else if (state->quote == '\"')
	{
		if (input[*i] == '$')
		{
			if (extract_variable_value(input, i, state, msh) == -1)
				return (-1);
		}
		else
		{
			if (try_ensure_buffer_capacity(state, 1, input[*i]) == -1)
				return (-1);
			(*i)++;
		}
	}
	return (0);
}

int	process_quoted_text(const char *input, int start,
	t_env_state *state, t_minish *msh)
{
	int		i;

	i = start + 1;
	while (input[i] && input[i] != state->quote)
	{
		if (process_quoted_text_loop(input, &i, state, msh) == -1)
			return (-1);
	}
	return (i);
}
