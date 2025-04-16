/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:02:41 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:43:02 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_env.h"

char	**env_list_to_str_arr(t_list *lst)
{
	char	**env;
	t_env	*env_node;
	size_t	size;

	env = NULL;
	if (lst == NULL)
		return (NULL);
	size = ft_lstsize(lst);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (env == NULL)
		return (NULL);
	size = 0;
	while (lst != NULL)
	{
		env_node = (t_env *)lst->content;
		env[size] = ft_strjoin3(env_node->key, "=", env_node->value);
		if (env[size] == NULL)
			return (free_split(env), NULL);
		lst = lst->next;
		size++;
	}
	env[size] = NULL;
	return (env);
}
