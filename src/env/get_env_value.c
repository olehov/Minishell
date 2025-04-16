/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:13:25 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:34:58 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_env.h"

char	*get_env_value(const char *var_name, t_list *lst)
{
	t_env	*env;

	env = ft_get_env(lst, (char *)var_name);
	if (env == NULL)
		return ("\0");
	return (env->value);
}
