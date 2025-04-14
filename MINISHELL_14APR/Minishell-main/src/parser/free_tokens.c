/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:58:22 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:39 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tokens(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens && tokens[i].value)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
	tokens = NULL;
}
