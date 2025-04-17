/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:32:48 by mfedorys          #+#    #+#             */
/*   Updated: 2025/04/17 21:39:06 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>

static void	process_argument_token(t_token *tokens,
	t_cmd *cmd, t_minish *msh, int *i)
{
	char	*processed;
	char	*env_applied;

	processed = NULL;
	env_applied = NULL;
	(void)msh;
	if (tokens[*i].quote_char == '\'')
		env_applied = remove_outer_quotes(tokens[*i].value);
	else
		env_applied = process_env(tokens[*i].value, msh->env, msh, tokens[*i].quote_char);
	if (ft_strchr(tokens[*i].value, '=') && tokens[*i].quote_char != '\'')
		processed = get_processed(env_applied, tokens, *i);
	else
	{
		if (!tokens[*i].in_quotes)
			processed = remove_quotes(env_applied);
		else
			processed = remove_quotes(env_applied);
	}
	free(env_applied);
	add_arg(cmd, processed);
}

static int	parse_single_command_from_tokens_loop(t_token *tokens,
	t_minish *msh, int *i, t_cmd *cmd)
{
	int	status;

	status = 0;
	if ((!tokens[*i].in_quotes && ft_strcmp(tokens[*i].value, "|") == 0)
		|| handle_redirects(i, cmd, tokens) == 1)
	{
		(*i)++;
		return (1);
	}
	else if (!tokens[*i].in_quotes
		&& ft_strcmp(tokens[*i].value, "<<") == 0 && tokens[*i + 1].value)
	{
		status = parce_heredoc(msh, i, cmd);
		if (status == -1)
			return (-1);
		else if (status == 1)
			return (1);
	}
	else
		process_argument_token(tokens, cmd, msh, i);
	(*i)++;
	return (0);
}

t_cmd	*parse_single_command_from_tokens(t_token *tokens,
	t_minish *msh)
{
	t_cmd	*cmd;
	int		status;
	int		i;

	i = 0;
	cmd = init_cmd_node();
	while (tokens[i].value)
	{
		status = parse_single_command_from_tokens_loop(tokens,
				msh, &i, cmd);
		if (status == 1)
			continue ;
		else if (status == -1)
			return (free_cmd_node(cmd), NULL);
	}
	return (cmd);
}

int	handle_heredoc_quote(char **result, size_t *i)
{
	size_t	start;
	size_t	end;
	char	*tmp;

	*i += 2;
	while ((*result)[*i] && ft_isspace((*result)[*i]))
		(*i)++;
	start = *i;
	find_delimiter_bounds(*result, &start, &end);
	if ((*result)[start] != '\'' && (*result)[start] != '"')
	{
		tmp = insert_quotes_around_delim(*result, start, end);
		if (!tmp)
			return (0);
		free(*result);
		*result = tmp;
		*i = end + 2;
	}
	return (1);
}
