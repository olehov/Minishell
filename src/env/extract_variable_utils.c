/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variable_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:26:00 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/17 14:17:10 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_env.h"
#include "../../include/process_env_utils.h"

int	extract_quoted_text(const char *input, int *i,
	t_env_state *state, t_minish *msh)
{
	state->quote = input[*i];
	*i = process_quoted_text(input, *i, state, msh);
	if (*i == -1)
		return (-1);
	return (0);
}

static int	extract_qoutes(const char *input, int *i,
	t_env_state *state, t_minish *msh)
{
	if (input[*i] == '"')
	{
		if (extract_quoted_text(input, i, state, msh) == -1)
			return (-1);
		return (1);
	}
	else if (input[*i] == '\'')
	{
		if (state->quote == 0)
		{
			if (extract_quoted_text(input, i, state, msh) == -1)
				return (-1);
		}
		else
		{
			if (try_ensure_buffer_capacity(state, 1, input[*i]) == -1)
				return (-1);
			(*i)++;
		}
		return (1);
	}
	return (0);
}

int	extract_variable(const char *input, int *i,
	t_env_state *state, t_minish *msh)
{
	int	err;

	while (input[*i])
	{
		err = extract_qoutes(input, i, state, msh);
		if (err == -1)
			return (-1);
		else if (input[*i] == '$' && !err)
		{
			if (extract_variable_value(input, i, state, msh) == -1)
				return (-1);
		}
		else if (input[*i] == '\\' && !err)
		{
			if (handle_escaping_variable(input, i, state) == -1)
				return (-1);
		}
		else
		{
			if (try_ensure_buffer_capacity(state, 1, input[(*i)++]) == -1)
				return (-1);
		}
	}
	return (0);
}
