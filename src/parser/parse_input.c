/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 15:27:11 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>

void	free_tokens(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens && tokens[i].value)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
	tokens = NULL;
}

int	parce_heredoc(t_minish *msh, int *i, t_cmd *cmd)
{
	t_heredoc	*heredoc;
	pid_t		pid;
	int			status;

	heredoc = init_heredoc(remove_outer_quotes(msh->tokens[++(*i)].value));
	if (heredoc == NULL)
	{
		msh->exit_code = 1;
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		set_heredoc_signals();
		status = ft_heredoc(heredoc, msh);
		free_cmd_node(cmd);
		free_tokens(msh->tokens);
		free_split(msh->pipe_split);
		clear_data(msh);
		free_shell(msh);
		if (status == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	msh->exit_code = ft_decode_wstatus(status);
	set_signals();
	add_redirection(cmd, _heredoc, heredoc->filename);
	if (msh->heredocs == NULL)
		msh->heredocs = ft_lstnew(heredoc);
	else
		ft_lstadd_back(&msh->heredocs, ft_lstnew(heredoc));
	return (0);
}

t_cmd *parse_single_command_from_tokens(t_token *tokens, t_minish *msh)
{
	t_cmd	*cmd = init_cmd_node();
	int		i = 0;

	while (tokens[i].value)
	{
		if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "|") == 0)
		{
			i++;
			continue ;
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
			int	status;

			status = parce_heredoc(msh, &i, cmd);
			if (status == -1)
				return (free_cmd_node(cmd), NULL);
			else if (status == 1)
				continue ;
		}
		else
		{
			char *processed = NULL;
			char *env_applied = NULL;
			if (!(tokens[i].in_quotes && tokens[i].quote_char == '\''))
				env_applied = process_env(tokens[i].value, msh->env, msh);
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

// char	*ft_get_input(char *input)
// {
// 	size_t	i;
// 	size_t	start;
// 	size_t	end;
// 	char	quote;
// 	int		in_quote;

// 	if (!input)
// 		return (NULL);
// 	i = 0;
// 	in_quote = 0;
// 	quote = 0;
// 	end = 0;
// 	start = 0;
// 	while (input[i])
// 	{
// 		if ((input[i] == '\'' || input[i] == '"') && !in_quote)
// 		{
// 			in_quote = 1;
// 			quote = input[i];
// 		}
// 		else if (in_quote && input[i] == quote)
// 			in_quote = 0;
// 		if (!in_quote && input[i] == '<' && input[i + 1] == '<')
// 		{
// 			i += 2;
// 			while (input[i] && ft_isspace(input[i]))
// 				i++;
// 			start = i;
// 			find_delimiter_bounds(input, &start, &end);
// 			return (insert_quotes_around_delim(input, start, end));
// 		}
// 		else
// 			i++;
// 	}
// 	return (ft_strdup(input));
// }


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
			return (free_cmd_list(first),
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
