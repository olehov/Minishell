/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escaping_variable.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:37:23 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 00:55:04 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_env.h"
#include "../../include/process_env_utils.h"

int	handle_escaping_variable(const char *input, int *i, t_env_state *state)
{
	if (input[*i] == '\\')
	{
		if (input[*i + 1] == '$' || input[*i + 1] == '\\'
			|| input[*i + 1] == '"')
		{
			if (try_ensure_buffer_capacity(state, 1, input[*i + 1]) == -1)
				return (-1);
			*i += 2;
			return (1);
		}
		else
		{
			if (try_ensure_buffer_capacity(state, 1, input[*i + 1]) == -1)
				return (-1);
			*i += 2;
			return (1);
		}
	}
	return (0);
}
