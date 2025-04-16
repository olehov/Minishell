/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:55:11 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>

static int	init_parse_input(t_cmd **first, t_cmd **last, int *i)
{
	*first = NULL;
	*last = NULL;
	*i = 0;
	return (0);
}

static t_cmd	*parse_single_pipe_segment(char *segment, t_cmd *prev,
											t_minish *msh)
{
	t_cmd	*cmd;

	msh->tokens = tokenize_with_quote_info(segment, msh);
	cmd = parse_single_command_from_tokens(msh->tokens, msh);
	free_tokens(msh->tokens);
	if (!cmd)
		return (NULL);
	cmd->prev = prev;
	return (cmd);
}

static int	parse_all_segments(t_minish *msh, t_cmd **first, t_cmd **last)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	while (msh->pipe_split[i])
	{
		cmd = parse_single_pipe_segment(msh->pipe_split[i], *last, msh);
		if (!cmd)
		{
			free_cmd_list(first);
			free_split(msh->pipe_split);
			msh->pipe_split = NULL;
			return (1);
		}
		if (!*first)
			*first = cmd;
		else
			(*last)->next = cmd;
		*last = cmd;
		i++;
	}
	return (0);
}

t_cmd	*parse_input(char *input, t_list *env, t_minish *msh)
{
	t_cmd	*first;
	t_cmd	*last;

	(void)env;
	init_parse_input(&first, &last, &(int){0});
	msh->pipe_split = split_outside_quotes(input, '|');
	if (parse_all_segments(msh, &first, &last))
		return (NULL);
	free_split(msh->pipe_split);
	msh->pipe_split = NULL;
	return (first);
}
