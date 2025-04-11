/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/11 17:29:18 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
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
			heredoc = init_heredoc(tokens[++i].value);
			if (heredoc == NULL)
			{
				g_last_exit_code = 1;
				continue ;
			}
			add_redirection(cmd, _heredoc, heredoc->filename);
			ft_heredoc(heredoc, msh->env);
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


char	*ft_get_input(char	*input)
{
	char	quote;
	char	*tmp;
	char	*joined;
	size_t	i;

	if (input == NULL)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i])
			{
				if (input[i] == '\'' || input[i] == '\"')
				{
					quote = input[i++];
					while (input[i] != quote && input[i] != '\0')
					{
						if (input[i + 1] == '\0')
						{
							tmp = readline("> ");
							if (tmp == NULL)
							{
								ft_putstr_fd(" unexpected EOF while looking for matching \'", STDERR_FILENO);
								ft_putchar_fd(quote, STDERR_FILENO);
								ft_putstr_fd("\'\n", STDERR_FILENO);
								return (NULL);
							}
							else
							{
								joined = ft_strjoin(input, tmp);
								if (joined == NULL)
									return (free(tmp), free(input), NULL);
								free(input);
								free(tmp);
								input = ft_strdup(joined);
								free(joined);
								if (input == NULL)
									return (NULL);
							}
						}
						i++;
					}
				}
				i++;
			}
		}
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
	char	*formated_input;

	(void)env;
	formated_input = ft_get_input(input);
	if (formated_input == NULL)
		return (NULL);
	char **pipe_split = split_outside_quotes(formated_input, '|');
	free(formated_input);
	while (pipe_split[i])
	{
		t_token *tokens = tokenize_with_quote_info(pipe_split[i]);
		cmd = parse_single_command_from_tokens(tokens, msh);
		cmd->prev = last;
		if (!first)
			first = cmd;
		else
			last->next = cmd;
		last = cmd;
		free(tokens);
		free(pipe_split[i]);
		i++;
	}
	free(pipe_split);
	return first;
}
