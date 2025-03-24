/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escaping_variable.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:37:23 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/24 15:37:40 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/process_env_utils.h"

int	handle_escaping_variable(const char *input, int *i, t_env_state *state)
{
	if (*i >= 2 && input[*i - 2] == '\\' && input[*i - 1] == '\\'
		&& input[*i] == '$')
	{
		if (try_ensure_buffer_capacity(state, 1, '\\') == -1)
			return (-1);
		(*i)++;
		return (1);
	}
	else if (*i >= 2 && input[*i - 2] != '\\'
		&& input[*i - 1] == '\\' && input[*i] == '$' && input[*i + 1] == '{')
	{
		if (try_ensure_buffer_capacity(state, 1, '$') == -1)
			return (-1);
		(*i)++;
		return (1);
	}
	return (0);
}
