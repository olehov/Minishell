/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:41:32 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:43:02 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_env.h"
#include "../../include/ft_utils.h"

char	**split_path(t_list *lst, char *key, char c)
{
	t_env	*env;

	env = ft_get_env(lst, key);
	if (env == NULL)
		return (NULL);
	return (ft_split(env->value, c));
}
