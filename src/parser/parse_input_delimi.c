/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_delimi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:04:27 by mfedorys          #+#    #+#             */
/*   Updated: 2025/04/18 00:33:53 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_parser.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>

static char	*create_result_with_quotes(char *prefix, char *delim, char *suffix)
{
	char	*quoted;
	char	*joined;
	char	*result;

	quoted = ft_strjoin3("\"", delim, "\"");
	if (!quoted)
		return (NULL);
	joined = ft_strjoin(prefix, quoted);
	free(quoted);
	if (!joined)
		return (NULL);
	result = ft_strjoin(joined, suffix);
	free(joined);
	return (result);
}

char	*insert_quotes_around_delim(char *input, size_t start, size_t end)
{
	char	*prefix;
	char	*delim;
	char	*suffix;
	char	*result;

	prefix = ft_substr(input, 0, start);
	delim = ft_substr(input, start, end - start);
	suffix = ft_strdup(input + end);
	if (!prefix || !delim || !suffix)
		return (free(prefix), free(delim), free(suffix), NULL);
	result = create_result_with_quotes(prefix, delim, suffix);
	free(prefix);
	free(delim);
	free(suffix);
	return (result);
}

void	find_delimiter_bounds(char *input, size_t *start, size_t *end)
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

// bool	handle_redirects(int *i, t_cmd *cmd, t_token *tokens)
// {
// 	if (ft_strcmp(tokens[*i].value, "<") == 0 && tokens[*i + 1].value)
// 	{
// 		add_redirection(cmd, _redirect_in, tokens[++(*i)].value);
// 		return (1);
// 	}
// 	else if (ft_strcmp(tokens[*i].value, ">") == 0 && tokens[*i + 1].value)
// 	{
// 		add_redirection(cmd, _redirect_out, tokens[++(*i)].value);
// 		return (1);
// 	}
// 	else if (ft_strcmp(tokens[*i].value, ">>") == 0 && tokens[*i + 1].value)
// 	{
// 		add_redirection(cmd, _append_to_file, tokens[++(*i)].value);
// 		return (1);
// 	}
// 	return (0);
// }


bool	handle_redirects(int *i, t_cmd *cmd, t_token *tokens)
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

char	*get_processed(char *env_applied, t_token *tokens, int i)
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
		// processed = ft_strdup(env_applied);
	return (processed);
}
