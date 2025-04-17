/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:07 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:33:27 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_env.h"

static void	ft_lst_remove(t_list **lst, char *env)
{
	t_list	*node;
	t_list	*current_node;
	t_list	*prev;
	t_env	*del_env;
	t_env	*current_env;

	prev = NULL;
	current_node = *lst;
	node = ft_get_env_node(*lst, env);
	if (node == NULL)
		return ;
	del_env = (t_env *)(node->content);
	while (current_node != NULL)
	{
		current_env = (t_env *)(current_node->content);
		if (ft_strcmp(current_env->key, del_env->key) == 0)
			break ;
		prev = current_node;
		current_node = current_node->next;
	}
	if (prev == NULL)
		*lst = (*lst)->next;
	else
		prev->next = current_node->next;
	ft_lstdelone(current_node, free_env);
}

void	ft_env_unset(t_list **lst, char *env)
{
	if (*lst == NULL || env == NULL)
		return ;
	ft_lst_remove(lst, env);
}
