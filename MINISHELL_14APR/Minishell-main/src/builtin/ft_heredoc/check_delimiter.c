/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:18:40 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 17:19:00 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_heredoc.h"

bool	check_delimiter(const char *delimiter)
{
	if (delimiter == NULL)
	{
		errno = EINVAL;
		ft_putendl_fd(" unexpected end of file", STDERR_FILENO);
		return (false);
	}
	if (delimiter[0] == '\0')
	{
		errno = EINVAL;
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}
