/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_quoted_text.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:30:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/23 15:09:15 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/process_env_utils.h"

static int	handle_text(const char *input, int *i, t_env_state *state,
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

int	process_quoted_text(const char *input, int start,
	t_env_state *state)
{
	int		i;
	char	var_name[256];

	i = start + 1;
	if (try_ensure_buffer_capacity(state, 1, state->quote) == -1)
		return (-1);
	while (input[i] && input[i] != state->quote)
	{
		if (handle_text(input, &i, state, var_name) == -1)
			return (-1);
	}
	return (i);
}
