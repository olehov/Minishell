/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variable_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:26:00 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/22 18:08:35 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/process_env_utils.h"

static int	extract_variable_name(const char *input, int start,
	char *var_name, int max_len)
{
	int	i;
	int	var_index;

	i = start;
	var_index = 0;
	if (input[i] == '{')
	{
		i++;
		while (input[i] && input[i] != '}' && var_index < max_len - 1)
		{
			if (input[i] == '$')
				return (extract_variable_name(input, i, var_name, 256));
			var_name[var_index++] = input[i++];
		}
		if (input[i] == '}')
			i++;
	}
	else
	{
		while (input[i] && (isalnum(input[i]) || input[i] == '_')
			&& var_index < max_len - 1)
			var_name[var_index++] = input[i++];
	}
	var_name[var_index] = '\0';
	return (i);
}

int	extract_variable_value(const char *input, int	*i, t_env_state *state)
{
	char	var_name[256];

	*i = extract_variable_name(input, *i + 1, var_name, 256);
	if (append_variable_value(var_name, state, state->lst) == -1)
		return (-1);
	return (0);
}


int	extract_quoted_text(const char *input, int *i,
	t_env_state *state)
{
	state->quote = input[*i];
	*i = process_quoted_text(input, *i, state);
	if (*i == -1)
		return (-1);
	return (0);
}


int	extract_variable(const char *input, int *i, t_env_state *state)
{
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			if (extract_quoted_text(input, i, state) == -1)
				return (-1);
		}
		else if (input[*i] == '$' && input[*i + 1] != ' '
			&& input[*i + 1] != '?')
		{
			if (extract_variable_value(input, i, state) == -1)
				return (-1);
		}
		else if (input[*i] == '\\')
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
