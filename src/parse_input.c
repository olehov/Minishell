/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/08 18:19:39 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>
#include <unistd.h>

// Ініціалізація структури команди
t_cmd	*init_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->delimiter = NULL;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->redirect_lst = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	return (cmd);
}

void	ft_set_quote(char *quote, char value)
{
	if (!(*quote))
		*quote = value;
	else if (*quote == value)
		*quote = 0;
}

char	**split_outside_quotes(char *input, char delimiter)
{
	char	**result;
	int		i;
	int		j;
	int		start;
	char	quote;

	result = malloc(sizeof(char *) * (ft_strlen(input) / 2 + 2));
	i = 0;
	j = 0;
	start = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"'))
			ft_set_quote(&quote, input[i]);
		else if (input[i] == delimiter && !quote)
		{
			result[j++] = ft_substr(input, start, i - start);
			start = i + 1;
		}
		i++;
	}
	if (i > start)
		result[j++] = ft_substr(input, start, i - start);
	result[j] = NULL;
	return (result);
}

// Токенізація з обліком лапок та з'єднанням суміжних токенів
// Тепер: лапки не знімаються, вони залишаються в token->value, але помічаються quote_char
// Після токенізації: process_env, потім remove_outer_quotes

char	*remove_outer_quotes(char *str)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
	{
		new_str = ft_substr(str, 1, len - 2);
		return (new_str);
	}
	return (ft_strdup(str));
}

bool	is_reddirect(char c)
{
	if (c == '<' || c == '>')
	{
		return (1);
	}
	return (0);
}

t_token *tokenize_with_quote_info(char *input)
{
	t_token *tokens = malloc(sizeof(t_token) * (ft_strlen(input) + 2));
	int i = 0, j = 0;
	char quote = 0;
	char *accum = NULL;
	char *part;
	int in_quotes = 0;
	char quote_char = 0;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break;

		if (input[i] == '\'' || input[i] == '"')
		{
			int start = i;
			quote = input[i++];
			quote_char = quote;
			in_quotes = 1;
			while (input[i] && input[i] != quote)
				i++;
			part = ft_substr(input, start, (i + 1) - start);
			accum = accum ? ft_strjoin(accum, part) : ft_strdup(part);
			free(part);
			if (input[i] == quote)
				i++;
			quote = 0;
		}
		else if ((input[i] == '<' || input[i] == '>') && input[i + 1] == input[i])
		{
			if (accum)
			{
				tokens[j].value = accum;
				tokens[j].in_quotes = in_quotes;
				tokens[j].quote_char = quote_char;
				j++;
				accum = NULL;
				in_quotes = 0;
				quote_char = 0;
			}
			// Heredoc token
			tokens[j].value = ft_substr(input, i, 2);
			tokens[j].in_quotes = 0;
			tokens[j].quote_char = 0;
			j++;
			i += 2;

			// Handle inline delimeter with quotes (e.g., <<EOF"" or <<EOF'')
			if (input[i] == '\'' || input[i] == '"')
			{
				quote = input[i++];
				quote_char = quote;
				in_quotes = 1;
				int start = i;
				while (input[i] && input[i] != quote)
					i++;
				part = ft_substr(input, start, i - start);
				accum = ft_strdup(part);
				free(part);
				if (input[i] == quote)
					i++;
				// Store the full quoted token
				tokens[j].value = accum;
				tokens[j].in_quotes = 1;
				tokens[j].quote_char = quote_char;
				j++;
				accum = NULL;
				in_quotes = 0;
				quote_char = 0;
			}
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			if (accum)
			{
				tokens[j].value = accum;
				tokens[j].in_quotes = in_quotes;
				tokens[j].quote_char = quote_char;
				j++;
				accum = NULL;
				in_quotes = 0;
				quote_char = 0;
			}
			tokens[j].value = ft_substr(input, i, 1);
			tokens[j].in_quotes = 0;
			tokens[j].quote_char = 0;
			j++;
			i++;
		}
		else
		{
			int start = i;
			while (input[i] && !ft_isspace(input[i]) && input[i] != '<' && input[i] != '>' && input[i] != '\'' && input[i] != '"')
				i++;
			part = ft_substr(input, start, i - start);
			accum = accum ? ft_strjoin(accum, part) : ft_strdup(part);
			free(part);
		}

		if (!input[i] || ft_isspace(input[i]) || input[i] == '<' || input[i] == '>')
		{
			if (accum)
			{
				tokens[j].value = accum;
				tokens[j].in_quotes = in_quotes;
				tokens[j].quote_char = quote_char;
				j++;
				accum = NULL;
				in_quotes = 0;
				quote_char = 0;
			}
		}
	}

	if (accum)
	{
		tokens[j].value = accum;
		tokens[j].in_quotes = in_quotes;
		tokens[j].quote_char = quote_char;
		j++;
	}

	tokens[j].value = NULL;
	return tokens;
}

void	add_redirection(t_cmd *cmd,
	t_redirect_type type, bool has_pipe, char *path)
{
	char	*filename;

	(void)has_pipe;
	if (cmd == NULL || path == NULL)
		return ;
	// if (!has_pipe)
	// {
		filename = remove_quotes(path);
		if (filename == NULL)
			return ;
		if (!has_pipe)
		{
			if (cmd->redirect_lst == NULL)
				cmd->redirect_lst = ft_lstnew(
						init_redirect(filename, type));
			else
				ft_lstadd_back(&cmd->redirect_lst,
					ft_lstnew(init_redirect(filename, type)));
		}
		free(filename);
	// }
}

// // Парсинг одного рядка команди з урахуванням токенів
t_cmd *parse_single_command_from_tokens(t_token *tokens, t_minish *msh)
{
	t_cmd	*cmd = init_cmd_node();
	int		i = 0;
	bool	has_pipe = false;

	while (tokens[i].value)
	{
		if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "|") == 0)
		{
			has_pipe = true;
			i++;
			continue;
		}
		if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "<") == 0 && tokens[i + 1].value)
		{
			add_redirection(cmd, _redirect_in, has_pipe, tokens[++i].value);
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, ">") == 0 && tokens[i + 1].value)
		{
			add_redirection(cmd, _redirect_out, has_pipe, tokens[++i].value);
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, ">>") == 0 && tokens[i + 1].value)
		{
			add_redirection(cmd, _append_to_file, has_pipe, tokens[++i].value);
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "<<") == 0 && tokens[i + 1].value)
		{
			t_heredoc	*heredoc;
			cmd->delimiter = ft_strdup(tokens[++i].value);
			heredoc = init_heredoc(cmd->delimiter);
			if (heredoc == NULL)
			{
				g_last_exit_code = 1;
				continue ;
			}
			add_redirection(cmd, _heredoc, has_pipe, heredoc->filename);
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
	// free(input);
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


// Очистка командного списку
void free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd != NULL)
	{
		tmp = cmd;
		i = 0;
		if (cmd->args != NULL)
		{
			while (cmd->args[i] != NULL)
				free(cmd->args[i++]);
			free(cmd->args);
		}
		if (cmd->delimiter != NULL)
			free(cmd->delimiter);
		if (cmd->redirect_lst != NULL)
			ft_lstclear(&cmd->redirect_lst, free_redirect);
		cmd = cmd->next;
		free(tmp);
	}
}
