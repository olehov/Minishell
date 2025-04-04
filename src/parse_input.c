/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/04 16:24:33 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Ініціалізація структури команди
t_cmd	*init_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->delimiter = NULL;
	cmd->append_out = 0;
	cmd->redirect_in = 0;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

// Токенізація з обліком лапок та з'єднанням суміжних токенів
// t_token *tokenize_with_quote_info(char *input)
// {
// 	t_token *tokens = malloc(sizeof(t_token) * (ft_strlen(input) / 2 + 2));
// 	int i = 0, j = 0, start = 0;
// 	char quote = 0;
// 	char *accum = NULL;
// 	char current_quote = 0;

// 	while (input[i])
// 	{
// 		while (input[i] && ft_isspace(input[i]))
// 			i++;
// 		if (!input[i]) break;
// 		start = i;

// 		if (input[i] == '\'' || input[i] == '"')
// 		{
// 			quote = input[i++];
// 			current_quote = quote;
// 			start = i;
// 			while (input[i] && input[i] != quote)
// 				i++;
// 			char *part = ft_substr(input, start, i - start);
// 			accum = accum ? ft_strjoin(accum, part) : ft_strdup(part);
// 			free(part);
// 			if (input[i] == quote) i++;
// 		}
// 		else
// 		{
// 			start = i;
// 			while (input[i] && !ft_isspace(input[i]) && input[i] != '\'' && input[i] != '"')
// 				i++;
// 			char *part = ft_substr(input, start, i - start);
// 			accum = accum ? ft_strjoin(accum, part) : ft_strdup(part);
// 			free(part);
// 		}

// 		if (!input[i] || ft_isspace(input[i]))
// 		{
// 			tokens[j].value = accum;
// 			tokens[j].in_quotes = current_quote != 0;
// 			tokens[j].quote_char = current_quote;
// 			j++;
// 			accum = NULL;
// 			current_quote = 0;
// 		}
// 	}
// 	if (accum)
// 	{
// 		tokens[j].value = accum;
// 		tokens[j].in_quotes = current_quote != 0;
// 		tokens[j].quote_char = current_quote;
// 		j++;
// 	}
// 	tokens[j].value = NULL;
// 	return tokens;
// }

// // Парсинг одного рядка команди з урахуванням токенів
// t_cmd *parse_single_command_from_tokens(t_token *tokens)
// {
// 	t_cmd *cmd = init_cmd_node();
// 	int i = 0;

// 	while (tokens[i].value)
// 	{
// 		if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "<") == 0 && tokens[i + 1].value)
// 		{
// 			cmd->infile = ft_strdup(tokens[++i].value);
// 			cmd->redirect_in = 1;
// 		}
// 		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, ">") == 0 && tokens[i + 1].value)
// 		{
// 			cmd->outfile = ft_strdup(tokens[++i].value);
// 			cmd->append_out = 0;
// 		}
// 		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, ">>") == 0 && tokens[i + 1].value)
// 		{
// 			cmd->outfile = ft_strdup(tokens[++i].value);
// 			cmd->append_out = 1;
// 		}
// 		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "<<") == 0 && tokens[i + 1].value)
// 		{
// 			cmd->infile = ft_strdup(tokens[i].value);
// 			cmd->delimiter = ft_strdup(tokens[++i].value);
// 			add_arg(cmd, ft_strdup(HEREDOC_FILENAME_PATH));
// 		}
// 		else
// 		{
// 			char *processed;
// 			if (!(tokens[i].in_quotes && tokens[i].quote_char == '\''))
// 			{
// 				if (ft_strchr(tokens[i].value, '$'))
// 				{
// 					processed = process_env(tokens[i].value, g_minish.env);
// 					if (!processed)
// 						processed = ft_strdup("");
// 				}
// 				else
// 					processed = ft_strdup(tokens[i].value);
// 			}
// 			else
// 				processed = ft_strdup(tokens[i].value);

// 			add_arg(cmd, processed);
// 		}
// 		i++;
// 	}
// 	return cmd;
// }

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

t_token *tokenize_with_quote_info(char *input)
{
	t_token *tokens = malloc(sizeof(t_token) * (ft_strlen(input) / 2 + 2));
	int i = 0, j = 0, start = 0;
	char quote = 0;
	char *accum = NULL;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		start = i;

		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			char *part = ft_substr(input, start - 1, i - start + 2);
			accum = accum ? ft_strjoin(accum, part) : ft_strdup(part);
			free(part);
			if (input[i] == quote)
				i++;
		}
		else
		{
			start = i;
			while (input[i] && !ft_isspace(input[i])
				&& input[i] != '\'' && input[i] != '"')
				i++;
			char *part = ft_substr(input, start, i - start);
			accum = accum ? ft_strjoin(accum, part) : ft_strdup(part);
			free(part);
		}

		if (!input[i] || ft_isspace(input[i]))
		{
			tokens[j].value = accum;
			tokens[j].in_quotes = quote != 0;
			tokens[j].quote_char = quote;
			j++;
			accum = NULL;
			quote = 0;
		}
	}
	if (accum)
	{
		tokens[j].value = accum;
		tokens[j].in_quotes = quote != 0;
		tokens[j].quote_char = quote;
		j++;
	}
	tokens[j].value = NULL;
	return tokens;
}

// Парсинг одного рядка команди з урахуванням токенів
t_cmd *parse_single_command_from_tokens(t_token *tokens, t_minish *msh)
{
	t_cmd *cmd = init_cmd_node();
	int i = 0;

	while (tokens[i].value)
	{
		if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "<") == 0 && tokens[i + 1].value)
		{
			cmd->infile = ft_strdup(tokens[++i].value);
			cmd->redirect_in = 1;
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, ">") == 0 && tokens[i + 1].value)
		{
			cmd->outfile = ft_strdup(tokens[++i].value);
			cmd->append_out = 0;
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, ">>") == 0 && tokens[i + 1].value)
		{
			cmd->outfile = ft_strdup(tokens[++i].value);
			cmd->append_out = 1;
		}
		else if (!tokens[i].in_quotes && ft_strcmp(tokens[i].value, "<<") == 0 && tokens[i + 1].value)
		{
			cmd->infile = ft_strdup(tokens[i].value);
			cmd->delimiter = ft_strdup(tokens[++i].value);
			add_arg(cmd, ft_strdup(HEREDOC_FILENAME_PATH));
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
					// processed = ft_strdup(env_applied);
			}
			else if (!processed)
				// processed = ft_strdup(env_applied);
				processed = remove_outer_quotes(env_applied);
			free(env_applied);
			add_arg(cmd, processed);
		}
		i++;
	}
	return cmd;
}

// Парсинг усієї команди з пайпами та лапками
t_cmd *parse_input(char *input, t_list *env, t_minish *msh)
{
	t_cmd	*first = NULL;
	t_cmd	*last = NULL;
	t_cmd	*cmd;
	// t_cmd	*prev;
	(void)env;
	char **pipe_split = split_outside_quotes(input, '|');
	int i = 0;

	while (pipe_split[i])
	{
		t_token *tokens = tokenize_with_quote_info(pipe_split[i]);
		cmd = parse_single_command_from_tokens(tokens, msh);
		// prev = last;
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
		cmd->append_out = 0;
		cmd->redirect_in = 0;
		if (cmd->delimiter != NULL)
			free(cmd->delimiter);
		if (cmd->infile != NULL)
			free(cmd->infile);
		if (cmd->outfile != NULL)
			free(cmd->outfile);
		cmd = cmd->next;
		free(tmp);
	}
}
