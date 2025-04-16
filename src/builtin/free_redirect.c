/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:31:30 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:51:24 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_redirection.h"

void	free_redirect(void *value)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)value;
	if (redirect == NULL)
		return ;
	if (redirect->filename != NULL)
		free(redirect->filename);
	redirect->type = _reset;
	free(redirect);
	value = NULL;
	value = NULL;
}
