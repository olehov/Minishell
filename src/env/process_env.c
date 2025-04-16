/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:17:14 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:16:36 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_env.h"
#include "../../include/process_env_utils.h"

static int	check_unsupported_line(const char *input)
{
	size_t		i;

	i = 0;
	while (input[i])
	{
		if (i > 1 && input[i - 2] == '\\' && input[i - 1] == '\\'
			&& input[i] == '$' && input[i + 1] == '{')
		{
			i++;
			while (input[i] && input[i] != '}')
			{
				if (input[i] == '$' || input[i] == ' ')
					return (0);
				i++;
			}
		}
		if (i > 1 && input[i - 2] != '\\' && input[i - 1] == '\\'
			&& input[i] == '$' && input[i + 1] == '{')
			return (1);
		i++;
	}
	return (1);
}

char	*process_env(const char *input, t_list *lst, t_minish *msh)
{
	int			i;
	t_env_state	state;

	if (check_unsupported_line(input) == 0)
		return (NULL);
	state.result_size = ft_strlen(input) * 2 + 1;
	state.result = ft_calloc(state.result_size, sizeof(char));
	if (!state.result)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	state.res_index = 0;
	i = 0;
	state.lst = lst;
	if (extract_variable(input, &i, &state, msh) == -1)
		return (NULL);
	state.result[state.res_index] = '\0';
	return (state.result);
}
