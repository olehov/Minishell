/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 06:24:51 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 06:25:33 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_utils.h"

void	print_syntax_err(char *str)
{
	if (!str || *str == '\0')
		ft_putendl_fd(" syntax error near unexpected token `newline'",
			STDERR_FILENO);
	else if (str[0] == '>' && str[1] == '>' && str[2] != '\0')
		ft_putendl_fd(" syntax error near unexpected token `>>'",
			STDERR_FILENO);
	else if (str[0] == '<' && str[1] == '<' && str[2] != '\0')
		ft_putendl_fd(" syntax error near unexpected token `<<'",
			STDERR_FILENO);
	else if (str[0] == '>' && str[1] != '\0')
		ft_putendl_fd(" syntax error near unexpected token `>'", STDERR_FILENO);
	else if (str[0] == '<' && str[1] != '\0')
		ft_putendl_fd(" syntax error near unexpected token `<'", STDERR_FILENO);
	else if (str[0] == '|')
		ft_putendl_fd(" syntax error near unexpected token `|'", STDERR_FILENO);
	else
		ft_putendl_fd(" syntax error near unexpected token `newline'",
			STDERR_FILENO);
}
