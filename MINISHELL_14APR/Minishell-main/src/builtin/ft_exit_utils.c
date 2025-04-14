/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:24:11 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 18:27:45 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_data(t_minish *msh)
{
	rl_clear_history();
	if (msh->cmd != NULL)
		free_cmd_list(&msh->cmd);
	free_shell(msh);
}

bool	is_only_digit(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}
