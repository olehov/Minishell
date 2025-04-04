/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:15:16 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/03 16:17:45 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	try_replace(t_list **lst, t_env *env)
{
	t_list	*tmp_node;

	if (*lst == NULL || env == NULL)
		return (-1);
	tmp_node = ft_get_env_node(*lst, env->key);
	if (tmp_node == NULL)
		return (0);
	free_env(tmp_node->content);
	tmp_node->content = env;
	return (1);
}

static void	replace(t_list **lst, t_env *env)
{
	if (*lst == NULL)
		*lst = ft_lstnew(env);
	else
		ft_lstadd_back(lst, ft_lstnew(env));
}

int	ft_set_env(t_list **lst, char	*env)
{
	t_env	*var;
	char	**tmp;
	char	*tmp_var;
	size_t	i;

	i = 0;
	if (env == NULL)
		return (-1);
	tmp = split_outside_quotes(env, ' ');
	if (tmp == NULL)
		return (-1);
	while (tmp[i] != NULL)
	{
		tmp_var = remove_quotes(tmp[i++]);
		var = parce_env(tmp_var);
		if (var == NULL)
			return (free_split(tmp), -1);
		else if (var->value[0] == '\0')
			free_env(var);
		else if (try_replace(lst, var) == 0)
			replace(lst, var);
		free(tmp_var);
	}
	return (ft_free_2d_array(tmp, i), 0);
}
