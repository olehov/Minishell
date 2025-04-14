/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfedorys <mfedorys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 19:58:19 by mfedorys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>

char	*ft_get_input(char *input)
{
	size_t	i;
	char	quote;
	int		in_quote;
	char	*result;

	if (!input)
		return (NULL);
	result = ft_strdup(input);
	if (!result)
		return (NULL);
	i = 0;
	in_quote = 0;
	quote = 0;
	while (result[i])
	{
		init_quote_state(result[i], &in_quote, &quote);
		if (!in_quote && result[i] == '<' && result[i + 1] == '<')
		{
			if (!handle_heredoc_quote(&result, &i))
				return (NULL);
			continue ;
		}
		i++;
	}
	return (result);
}

static int	init_parse_input(t_cmd **first, t_cmd **last, int *i,
								char **formatted)
{
	*first = NULL;
	*last = NULL;
	*i = 0;
	*formatted = NULL;
	return (0);
}

static t_cmd	*parse_single_pipe_segment(char *segment, t_cmd *prev,
											t_minish *msh)
{
	t_cmd	*cmd;

	msh->tokens = tokenize_with_quote_info(segment);
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
	char	*formatted_input;

	(void)env;
	init_parse_input(&first, &last, &(int){0}, &formatted_input);
	formatted_input = ft_get_input(input);
	if (!formatted_input)
		return (NULL);
	msh->pipe_split = split_outside_quotes(formatted_input, '|');
	free(formatted_input);
	if (parse_all_segments(msh, &first, &last))
		return (NULL);
	free_split(msh->pipe_split);
	return (first);
}
