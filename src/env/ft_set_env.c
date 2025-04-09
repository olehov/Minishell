/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:15:16 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 22:20:11 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void	add_or_update_env(t_list **lst, t_env *var)
{
	t_list	*cur;
	t_env	*item;
	t_env	*new_var;

	cur = *lst;
	while (cur)
	{
		item = (t_env *)cur->content;
		if (ft_strcmp(item->key, var->key) == 0)
		{
			free(item->value);
			item->value = ft_strdup(var->value);
			return ;
		}
		cur = cur->next;
	}
	new_var = malloc(sizeof(t_env));
	if (new_var == NULL)
		return ;
	new_var->key = ft_strdup(var->key);
	new_var->value = ft_strdup(var->value);
	ft_lstadd_back(lst, ft_lstnew(new_var));
}

static int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_error(char *str)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
	g_last_exit_code = EXIT_FAILURE;
}

int	ft_set_env(t_list **lst, char *env)
{
	t_env	*var;
	char	**tmp;
	int		i;

	i = 0;
	if (!env)
		return (-1);
	tmp = split_outside_quotes(env, ' ');
	if (!tmp)
		return (-1);
	while (tmp[i])
	{
		if (!is_valid_identifier(tmp[i]))
		{
			print_error(tmp[i++]);
			continue ;
		}
		var = parce_env(tmp[i]);
		if (var == NULL)
			return (free_split(tmp), -1);
		add_or_update_env(lst, var);
		i++;
	}
	free_split(tmp);
	return (0);
}
