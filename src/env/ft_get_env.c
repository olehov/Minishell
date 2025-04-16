/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:54 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:43:02 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_env.h"

t_list	*ft_get_env_node(t_list *lst, char *key)
{
	t_env	*env;

	if (lst == NULL || key == NULL)
		return (NULL);
	while (lst != NULL)
	{
		env = (t_env *)(lst->content);
		if (ft_strcmp(env->key, key) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_env	*ft_get_env(t_list *lst, char *key)
{
	t_list	*node;

	node = ft_get_env_node(lst, key);
	if (node != NULL)
		return ((t_env *)(node->content));
	return (NULL);
}
