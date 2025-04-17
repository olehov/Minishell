/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:21:16 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:31:37 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_env.h"

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
