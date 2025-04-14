/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:19:18 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/13 17:22:24 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_key(char *env)
{
	char	*key;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (env[size] != '=' && env[size] != '\0')
		size++;
	if (size == 0)
		return (NULL);
	key = malloc(sizeof(char) * (size + 1));
	if (key == NULL)
		return (NULL);
	while (env[i] != '=' && env[i] != '\0')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static char	*get_value(char *key, char *env)
{
	char	*value;
	size_t	i;
	size_t	j;

	if (key == NULL || env == NULL)
		return (NULL);
	i = ft_strlen(key);
	if (env[i] == '=')
		i++;
	j = 0;
	value = ft_calloc(sizeof(char), ((ft_strlen(env) - i) + 1));
	if (value == NULL)
		return (NULL);
	while (env[i] != '\0')
	{
		value[j] = env[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

t_env	*parce_env(char *env)
{
	t_env	*var;
	size_t	j;

	j = 0;
	if (env == NULL)
		return (NULL);
	var = malloc(sizeof(t_env));
	if (var == NULL)
		return (perror(strerror(ENOSPC)), NULL);
	var->key = ft_get_key(env);
	if (var->key == NULL)
		return (free(var), NULL);
	while (var->key[j])
	{
		if (var->key == NULL || ft_isdigit(var->key[0])
			|| (var->key[j + 1] == '\0' && ft_issign(var->key[j])))
			return (free(var->key), free(var), NULL);
		j++;
	}
	var->value = get_value(var->key, env);
	if (var->value == NULL)
		return (free(var->key), free(var), NULL);
	return (var);
}

static void	update_shell_level(t_list **lst)
{
	int		lvl;
	char	*shlvl;
	char	*tmp;

	if (*lst == NULL)
		return ;
	shlvl = get_env_value("SHLVL", *lst);
	if (shlvl == NULL)
		return ;
	lvl = ft_atoi(shlvl);
	lvl++;
	tmp = ft_itoa(lvl);
	if (tmp == NULL)
		return ;
	shlvl = ft_strjoin3("SHLVL", "=", tmp);
	free(tmp);
	if (shlvl == NULL)
		return ;
	ft_set_env(lst, shlvl);
	free(shlvl);
}

int	init_env(t_list **lst, char *env[])
{
	t_env	*var;
	int		i;

	i = 0;
	if (env == NULL)
		return (perror(strerror(EINVAL)), -1);
	while (env[i] != NULL)
	{
		var = parce_env(env[i++]);
		if (var == NULL)
			return (ft_lstclear(lst, free_env), -1);
		else if (*lst == NULL)
			*lst = ft_lstnew(var);
		else
			ft_lstadd_back(lst, ft_lstnew(var));
	}
	if (*lst != NULL)
		update_shell_level(lst);
	return (0);
}
