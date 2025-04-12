/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/12 19:54:13 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>


t_cmd *parse_single_command_from_tokens(t_token *tokens, t_minish *msh)
{
	t_cmd	*cmd = init_cmd_node();
	int		i = 0;

	while (tokens[i].value)
	{
		if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "|") == 0)
		{
			i++;
			continue;
		}
		if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "<") == 0 && tokens[i + 1].value)
		{
			add_redirection(cmd, _redirect_in, tokens[++i].value);
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, ">") == 0 && tokens[i + 1].value)
		{
			add_redirection(cmd, _redirect_out, tokens[++i].value);
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, ">>") == 0 && tokens[i + 1].value)
		{
			add_redirection(cmd, _append_to_file, tokens[++i].value);
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "<<") == 0 && tokens[i + 1].value)
		{
			t_heredoc	*heredoc;
			heredoc = init_heredoc(remove_outer_quotes(tokens[++i].value));
			if (heredoc == NULL)
			{
				g_last_exit_code = 1;
				continue ;
			}
			if (ft_heredoc(heredoc, msh->env) == -1)
			{
				return (free_cmd_node(cmd), free_heredoc(heredoc), NULL);
			}
			add_redirection(cmd, _heredoc, heredoc->filename);
			if (msh->heredocs == NULL)
				msh->heredocs = ft_lstnew(heredoc);
			else
				ft_lstadd_back(&msh->heredocs, ft_lstnew(heredoc));
		}
		else
		{
			char *processed = NULL;
			char *env_applied = NULL;
			if (!(tokens[i].in_quotes && tokens[i].quote_char == '\''))
				env_applied = process_env(tokens[i].value, msh->env);
			else
				env_applied = ft_strdup(tokens[i].value);
			if (ft_strchr(tokens[i].value, '='))
			{
				char *eq = ft_strchr(env_applied, '=');
				if (eq && tokens[i].quote_char != 0)
				{
					*eq = '\0';
					char *quoted_value = ft_strjoin3("\"", eq + 1, "\"");
					processed = ft_strjoin3(env_applied, "=", quoted_value);
					free(quoted_value);
				}
				else
					processed = remove_outer_quotes(env_applied);
			}
			else if (!processed)
				processed = remove_outer_quotes(env_applied);
			free(env_applied);
			add_arg(cmd, processed);
		}
		i++;
	}
	return cmd;
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
		return (ft_safe_free(prefix), ft_safe_free(delim), ft_safe_free(suffix), NULL);
	quoted = ft_strjoin3("\"", delim, "\"");
	joined = ft_strjoin(prefix, quoted);
	result = ft_strjoin(joined, suffix);
	ft_safe_free(prefix);
	ft_safe_free(delim);
	ft_safe_free(quoted);
	ft_safe_free(joined);
	ft_safe_free(suffix);
	return (result);
}


static void	find_delimiter_bounds(char *input, size_t *start, size_t *end)
{
	size_t	i = *start;
	char	quote;

	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			quote = input[i];
		while (input[i] != '\0' && input[i] != quote)
			i++;
		if (input[i] == '\0' || ft_isspace(input[i]) || input[i] == '<'
			|| input[i] == '>' || input[i] == '|'
			|| input[i] == '&' || input[i] == ';')
			break ;
		i++;
	}
	*end = i;
}




// static void	find_delimiter_bounds(char *input, size_t *start, size_t *end)
// {
// 	size_t	i = *start;

// 	while (input[i])
// 	{
// 		if (input[i] == '\'' || input[i] == '"')
// 			break;
// 		i++;
// 	}
// 	*end = i;
// }

char	*ft_get_input(char *input)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	quote;
	int		in_quote;

	if (!input)
		return (NULL);
	i = 0;
	in_quote = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && !in_quote)
		{
			in_quote = 1;
			quote = input[i];
		}
		else if (in_quote && input[i] == quote)
			in_quote = 0;
		if (!in_quote && input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] && ft_isspace(input[i]))
				i++;
			start = i;
			find_delimiter_bounds(input, &start, &end);
			return (insert_quotes_around_delim(input, start, end));
		}
		else
			i++;
	}
	return (ft_strdup(input));
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
	char **pipe_split = split_outside_quotes(formated_input, '|');
	ft_safe_free(formated_input);
	while (pipe_split[i])
	{
		t_token *tokens = tokenize_with_quote_info(pipe_split[i]);
		cmd = parse_single_command_from_tokens(tokens, msh);
		if (cmd == NULL)
			return (free_cmd_list(first), free(tokens), free_split(pipe_split), NULL);
		cmd->prev = last;
		if (!first)
			first = cmd;
		else
			last->next = cmd;
		last = cmd;
		ft_safe_free(tokens);
		ft_safe_free(pipe_split[i]);
		i++;
	}
	ft_safe_free(pipe_split);
	return first;
}
