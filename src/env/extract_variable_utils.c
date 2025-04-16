/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variable_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:26:00 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:15:15 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_env.h"
#include "../../include/process_env_utils.h"

static int	extract_variable_name(const char *input, int start,
	char *var_name, int max_len)
{
	int	i;
	int	var_index;

	i = start;
	var_index = 0;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_')
		&& var_index < max_len - 1)
		var_name[var_index++] = input[i++];
	var_name[var_index] = '\0';
	return (i);
}

static int	extract_last_exit_code(int *i, int *j,
	t_env_state *state, t_minish *msh)
{
	char	*exit_str;

	exit_str = ft_itoa(msh->exit_code);
	if (!exit_str)
		return (-1);
	if (ensure_buffer_capacity(state, ft_strlen(exit_str)) == -1)
		return (free(exit_str), -1);
	while (exit_str[*j])
		state->result[state->res_index++] = exit_str[(*j)++];
	free(exit_str);
	*i += 2;
	return (0);
}

int	extract_variable_value(const char *input, int *i,
	t_env_state *state, t_minish *msh)
{
	char	var_name[256];
	int		j;

	j = 0;
	if (input[*i + 1] == '?')
		return (extract_last_exit_code(i, &j, state, msh));
	if (!ft_isalpha(input[*i + 1]) && !ft_isdigit(input[*i + 1]))
	{
		if (ensure_buffer_capacity(state, sizeof(char)) == -1)
			return (-1);
		state->result[state->res_index++] = input[(*i)++];
		return (0);
	}
	*i = extract_variable_name(input, *i + 1, var_name, 256);
	if (append_variable_value(var_name, state, state->lst) == -1)
		return (-1);
	return (0);
}

int	extract_quoted_text(const char *input, int *i,
	t_env_state *state, t_minish *msh)
{
	state->quote = input[*i];
	*i = process_quoted_text(input, *i, state, msh);
	if (*i == -1)
		return (-1);
	return (0);
}

int	extract_variable(const char *input, int *i,
	t_env_state *state, t_minish *msh)
{
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (extract_quoted_text(input, i, state, msh) == -1)
				return (-1);
		}
		else if (input[*i] == '$')
		{
			if (extract_variable_value(input, i, state, msh) == -1)
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
