/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:04 by mfedorys          #+#    #+#             */
/*   Updated: 2025/04/17 19:34:42 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>

static int	checking_rest(char *input, int flag)
{
	int	i;

	i = 0;
	while (input[++i])
	{
		if (flag == 1
			&& (input[i] == '|' || input[i] == '<' || input[i] == '>'))
			return (1);
		else if (flag == 1 && ft_isalnum(input[i])
			&& !ft_isspace(input[i]) && input[i] != '\0')
			flag = 0;
		if (input[i] == '|' || (input[i] == '<' && input[i + 1] != '<')
			|| (input[i] == '>' && input[i + 1] != '>'))
			flag = 1;
		else if ((input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
		{
			flag = 1;
			i++;
		}
	}
	return (flag);
}

int	ft_syntax_error(char *input)
{
	int	i;
	int	flag;

	i = -1;
	if (input[++i] == '|')
		return (1);
	while (ft_isspace(input[++i]))
	{
		if (input[i + 1] == '|')
			return (1);
	}
	flag = 0;
	flag = checking_rest(input, flag);
	return (flag);
}
