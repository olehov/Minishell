/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:19:18 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/22 15:48:58 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_key(char *env)
{
	char	*key;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (env[size] != '=' && env[size] != '\0')
		size++;
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

	if (env == NULL)
		return (NULL);
	var = malloc(sizeof(t_env));
	if (var == NULL)
		return (perror(strerror(ENOSPC)), NULL);
	var->key = ft_get_key(env);
	if (var->key == NULL)
		return (free(var), NULL);
	var->value = get_value(var->key, env);
	if (var->value == NULL)
		return (free(var->key), free(var), NULL);
	return (var);
}

void	free_env(void *env)
{
	if (env == NULL)
		return ;
	if (((t_env *)env)->key != NULL)
		free(((t_env *)env)->key);
	if (((t_env *)env)->value != NULL)
		free(((t_env *)env)->value);
	free(env);
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
	return (0);
}
