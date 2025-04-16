/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_variable_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:36:53 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:43:02 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_env.h"
#include "../../include/process_env_utils.h"

int	append_variable_value(const char *var_name, t_env_state *state, t_list *lst)
{
	char	*var_value;
	int		j;

	var_value = get_env_value(var_name, lst);
	if (ft_strcmp(var_value, "\0") == 0)
		return (1);
	if (ensure_buffer_capacity(state, ft_strlen(var_value)) == -1)
		return (-1);
	j = 0;
	while (var_value[j])
		state->result[state->res_index++] = var_value[j++];
	return (0);
}
