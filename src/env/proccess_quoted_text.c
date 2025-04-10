/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_quoted_text.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:30:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/10 15:39:19 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/process_env_utils.h"

int	handle_text(const char *input, int *i, t_env_state *state,
	char *var_name)
{
	(void)var_name;
	if (input[*i] == '\\')
	{
		if (handle_escaping_variable(input, i, state) == -1)
			return (-1);
	}
	else if (state->quote == '\'' && input[*i] == '\"')
	{
		if (extract_quoted_text(input, i, state) == -1)
			return (-1);
	}
	else if (state->quote == '\"' && input[*i] == '$' && input[*i + 1] != ' ')
	{
		if (extract_variable_value(input, i, state) == -1)
			return (-1);
	}
	else
	{
		if (try_ensure_buffer_capacity(state, 1, input[(*i)++]) == -1)
			return (-1);
	}
	return (0);
}

static int	process_quoted_text_loop(const char *input,
	int *i, t_env_state *state)
{
	if (state->quote == '\'' && input[*i])
	{
		if (try_ensure_buffer_capacity(state, 1, input[*i]) == -1)
			return (-1);
		i++;
	}
	else if (state->quote == '\"')
	{
		if (input[*i] == '$')
		{
			if (extract_variable_value(input, i, state) == -1)
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

int	process_quoted_text(const char *input, int start, t_env_state *state)
{
	int		i;

	i = start + 1;
	while (input[i] && input[i] != state->quote)
	{
		if (process_quoted_text_loop(input, &i, state) == -1)
			return (-1);
	}
	return (i);
}
