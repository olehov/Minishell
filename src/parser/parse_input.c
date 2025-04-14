/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 18:37:48 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>

static bool	handle_redirects(int *i, t_cmd *cmd, t_token *tokens)
{
	if (!tokens[*i].in_quotes
		&& ft_strcmp(tokens[*i].value, "<") == 0 && tokens[*i + 1].value)
	{
		add_redirection(cmd, _redirect_in, tokens[++(*i)].value);
		return (1);
	}
	else if (!tokens[*i].in_quotes
		&& ft_strcmp(tokens[*i].value, ">") == 0 && tokens[*i + 1].value)
	{
		add_redirection(cmd, _redirect_out, tokens[++(*i)].value);
		return (1);
	}
	else if (!tokens[*i].in_quotes
		&& ft_strcmp(tokens[*i].value, ">>") == 0 && tokens[*i + 1].value)
	{
		add_redirection(cmd, _append_to_file, tokens[++(*i)].value);
		return (1);
	}
	return (0);
}

static char	*get_processed(char *env_applied, t_token *tokens, int i)
{
	char	*eq;
	char	*quoted_value;
	char	*processed;

	eq = NULL;
	quoted_value = NULL;
	processed = NULL;
	eq = ft_strchr(env_applied, '=');
	if (eq && tokens[i].quote_char != 0)
	{
		*eq = '\0';
		quoted_value = ft_strjoin3("\"", eq + 1, "\"");
		processed = ft_strjoin3(env_applied, "=", quoted_value);
		free(quoted_value);
	}
	else
		processed = remove_outer_quotes(env_applied);
	return (processed);
}

static void	process_argument_token(t_token *tokens,
	t_cmd *cmd, t_minish *msh, int *i)
{
	char	*processed;
	char	*env_applied;

	processed = NULL;
	env_applied = NULL;
	if (!(tokens[*i].in_quotes && tokens[*i].quote_char == '\''))
		env_applied = process_env(tokens[*i].value, msh->env, msh);
	else
		env_applied = ft_strdup(tokens[*i].value);
	if (ft_strchr(tokens[*i].value, '='))
	{
		processed = get_processed(env_applied, tokens, *i);
	}
	else if (!processed)
		processed = remove_outer_quotes(env_applied);
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





static char	*insert_quotes_around_delim(char *input, size_t start, size_t end)
{
	char	*prefix;
	char	*delim;
	char	*quoted;
	char	*suffix;
	char	*joined;
	char	*result;

	prefix = ft_substr(input, 0, start);
	delim = ft_substr(input, start, end - start);
	suffix = ft_strdup(input + end);
	if (!prefix || !delim || !suffix)
		return (free(prefix), free(delim), free(suffix), NULL);
	quoted = ft_strjoin3("\"", delim, "\"");
	joined = ft_strjoin(prefix, quoted);
	result = ft_strjoin(joined, suffix);
	free(prefix);
	free(delim);
	free(quoted);
	free(joined);
	free(suffix);
	return (result);
}


static void	find_delimiter_bounds(char *input, size_t *start, size_t *end)
{
	size_t	i;
	char	quote;

	i = *start;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			quote = input[i++];
			while (input[i] != '\0' && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++;
			continue ;
		}
		if (input[i] == '\0' || ft_isspace(input[i]) || input[i] == '<'
			|| input[i] == '>' || input[i] == '|'
			|| input[i] == '&' || input[i] == ';')
			break ;
		i++;
	}
	*end = i;
}





char	*ft_get_input(char *input)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	quote;
	int		in_quote;
	char	*result;
	char	*tmp;

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
		if ((result[i] == '\'' || result[i] == '"') && !in_quote)
		{
			in_quote = 1;
			quote = result[i];
		}
		else if (in_quote && result[i] == quote)
			in_quote = 0;

		if (!in_quote && result[i] == '<' && result[i + 1] == '<')
		{
			i += 2;
			while (result[i] && ft_isspace(result[i]))
				i++;
			start = i;
			find_delimiter_bounds(result, &start, &end);
			if (result[start] != '\'' && result[start] != '"')
			{
				tmp = insert_quotes_around_delim(result, start, end);
				free(result);
				result = tmp;
				i = end + 2;
				continue ;
			}
		}
		i++;
	}
	return (result);
}

t_cmd *parse_input(char *input, t_list *env, t_minish *msh)
{
	t_cmd	*first = NULL;
	t_cmd	*last = NULL;
	int		i = 0;
	t_cmd	*cmd;
	char	*formated_input = NULL;

	(void)env;
	formated_input = ft_get_input(input);
	if (formated_input == NULL)
		return (NULL);
	msh->pipe_split = split_outside_quotes(formated_input, '|');
	free(formated_input);
	while (msh->pipe_split[i])
	{
		msh->tokens = tokenize_with_quote_info(msh->pipe_split[i]);
		cmd = parse_single_command_from_tokens(msh->tokens, msh);
		free_tokens(msh->tokens);
		if (cmd == NULL)
			return (free_cmd_list(&first),
				free_split(msh->pipe_split), NULL);
		cmd->prev = last;
		if (!first)
			first = cmd;
		else
			last->next = cmd;
		last = cmd;
		i++;
	}
	free_split(msh->pipe_split);
	return (first);
}
