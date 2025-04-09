/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:27:39 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 20:14:45 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_redirection.h"

t_redirect	*init_redirect(char *filename, t_redirect_type type)
{
	t_redirect	*redirect;

	if (filename == NULL)
		return (NULL);
	redirect = malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->filename = ft_strdup(filename);
	if (redirect->filename == NULL)
		return (free(redirect), NULL);
	redirect->type = type;
	return (redirect);
}
