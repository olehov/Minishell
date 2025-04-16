/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:50:38 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 10:53:50 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_get_user(t_minish *msh)
{
	char	*user_value;
	char	*user;

	user_value = get_env_value("USER", msh->env);
	if (ft_strcmp(user_value, "\0") != 0)
		user = ft_strjoin3(CYAN, user_value, "'s" RESET "-" GRN "minishell");
	else
		user = ft_strjoin(GRN, "minishell");
	if (user == NULL)
		return (NULL);
	return (user);
}

char	*get_prompt(t_minish *msh)
{
	char	*prompt;
	char	*tmp;
	char	*user;
	char	*err_code;

	user = ft_get_user(msh);
	if (user == NULL)
		return (NULL);
	if (msh->exit_code == 0)
		prompt = ft_strjoin(user, RESET "> ");
	else
	{
		tmp = ft_strjoin(user, " " RED "[");
		if (tmp == NULL)
			return (free(user), NULL);
		err_code = ft_itoa(msh->exit_code);
		prompt = ft_strjoin3(tmp, err_code, "]" RESET "> ");
		free(tmp);
		if (err_code != NULL)
			free(err_code);
	}
	free(user);
	return (prompt);
}
