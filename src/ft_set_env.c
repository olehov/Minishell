/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:15:16 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/05 10:57:48 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void add_or_update_env(t_list **lst, t_env *var)
{
	t_list *cur = *lst;
	while (cur)
	{
		t_env *item = (t_env *)cur->content;
		if (ft_strcmp(item->key, var->key) == 0)
		{
			free(item->value);
			item->value = ft_strdup(var->value);
			return;
		}
		cur = cur->next;
	}
	t_env *new_var = malloc(sizeof(t_env));
	new_var->key = ft_strdup(var->key);
	new_var->value = ft_strdup(var->value);
	new_var->append = 0;
	ft_lstadd_back(lst, ft_lstnew(new_var));
}

static void append_variable_value(t_list **lst, t_env *var)
{
	t_list *cur = *lst;
	while (cur)
	{
		t_env *item = (t_env *)cur->content;
		if (ft_strcmp(item->key, var->key) == 0)
		{
			char *joined = ft_strjoin(item->value, var->value);
			free(item->value);
			item->value = joined;
			return;
		}
		cur = cur->next;
	}
	// Якщо змінна ще не існує — додаємо її як нову
	add_or_update_env(lst, var);
}


static int is_valid_identifier(const char *str)
{
	int i = 0;
	if (!str || !str[0] || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int ft_set_env(t_list **lst, char *env)
{
	if (!env || env[0] == '\0')
	{
		t_list *cur = *lst;
		while (cur)
		{
			t_env *var = (t_env *)cur->content;
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(var->key, STDOUT_FILENO);
			if (var->value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(var->value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			ft_putchar_fd(' ', STDOUT_FILENO);
			cur = cur->next;
		}
		return (0);
	}
	t_env *var;
	char **tmp;
	int i = 0;

	if (!env)
		return (-1);
	tmp = split_outside_quotes(env, ' ');
	if (!tmp)
		return (-1);
	while (tmp[i])
	{
		if (!is_valid_identifier(tmp[i]))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(tmp[i], STDERR_FILENO);
			ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
			g_last_exit_code = EXIT_FAILURE;
			i++;
			continue ;
		}
		var = parce_env(tmp[i]);
		if (var == NULL)
		{
			free_split(tmp);
			return (-1);
		}
		if (get_env_value(var->key, *lst))
			append_variable_value(lst, var);
		else
			add_or_update_env(lst, var);
		i++;
	}
	free_split(tmp);
	return (0);
}



// static int	try_replace(t_list **lst, t_env *env)
// {
// 	t_list	*tmp_node;

// 	if (*lst == NULL || env == NULL)
// 		return (-1);
// 	tmp_node = ft_get_env_node(*lst, env->key);
// 	if (tmp_node == NULL)
// 		return (0);
// 	free_env(tmp_node->content);
// 	tmp_node->content = env;
// 	return (1);
// }

// static void	replace(t_list **lst, t_env *env)
// {
// 	if (*lst == NULL)
// 		*lst = ft_lstnew(env);
// 	else
// 		ft_lstadd_back(lst, ft_lstnew(env));
// }

// int	ft_set_env(t_list **lst, char	*env)
// {
// 	t_env	*var;
// 	char	**tmp;
// 	char	*tmp_var;
// 	size_t	i;

// 	i = 0;
// 	if (env == NULL)
// 		return (-1);
// 	tmp = split_outside_quotes(env, ' ');
// 	if (tmp == NULL)
// 		return (-1);
// 	while (tmp[i] != NULL)
// 	{
// 		tmp_var = remove_quotes(tmp[i++]);
// 		var = parce_env(tmp_var);
// 		if (var == NULL)
// 			return (free_split(tmp), -1);
// 		else if (var->value[0] == '\0')
// 			free_env(var);
// 		else if (try_replace(lst, var) == 0)
// 			replace(lst, var);
// 		free(tmp_var);
// 	}
// 	return (ft_free_2d_array(tmp, i), 0);
// }
