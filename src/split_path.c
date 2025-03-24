/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:41:32 by ogrativ           #+#    #+#             */
/*   Updated: 2024/12/11 15:01:41 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_path(t_list *lst, char *key, char c)
{
	t_env	*env;

	env = ft_get_env(lst, key);
	if (env == NULL)
		return (NULL);
	return (ft_split(env->value, c));
}
