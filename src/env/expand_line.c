/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:01:57 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:53:23 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_single_char(char c, char *result)
{
	char	*ch;
	char	*tmp;

	ch = ft_substr(&c, 0, 1);
	if (result)
		tmp = ft_strjoin(result, ch);
	else
		tmp = ft_strdup(ch);
	free(ch);
	free(result);
	return (tmp);
}

static char	*expand_single_quote(const char *line, int *i)
{
	int		start;
	char	*result;

	start = *i + 1;
	*i += 1;
	while (line[*i] && line[*i] != '\'')
		*i += 1;
	result = ft_substr(line, start, *i - start);
	*i += 1;
	return (result);
}

static char	*expand_dollar(const char *line, int *i, t_minish *msh)
{
	char	*expanded;
	int		j;

	j = *i;
	expanded = process_env(&line[j], msh->env, msh);
	if (!expanded)
		return (NULL);
	while (line[*i] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
		*i += 1;
	*i += 1;
	return (expanded);
}

static void	join_tmp_to_result(char **result, char *tmp)
{
	char	*joined;

	if (*result)
	{
		joined = ft_strjoin(*result, tmp);
		free(*result);
		*result = joined;
	}
	else
		*result = ft_strdup(tmp);
	free(tmp);
}

char	*expand_line(char *line, t_minish *msh, int i)
{
	char	*result;
	char	*tmp;
	bool	in_dquote;

	result = NULL;
	tmp = NULL;
	in_dquote = false;
	while (line[i])
	{
		if (line[i] == '"')
			in_dquote = !in_dquote;
		else if (line[i] == '\'' && !in_dquote)
			tmp = expand_single_quote(line, &i);
		else if (line[i] == '$' && in_dquote)
			tmp = expand_dollar(line, &i, msh);
		else
			result = expand_single_char(line[i++], result);
		if (tmp)
		{
			if (result)
			{
				char *joined = ft_strjoin(result, tmp);
				free(result);
				result = joined;
			}
			else
				result = ft_strdup(tmp);
			free(tmp);
		}
	}
	if (!result)
		result = ft_strdup("");
	return result;
}

// char	*expand_line(char *line, t_minish *msh, int i)
// {
// 	char	*result;

// 	result = NULL;
// 	while (line[i] != '\0')
// 	{
// 		// printf("i: %i\n", i);
// 		//check that there are matching quotes ", ' before that
// 		if (line[i] == '\'')
// 		{
// 			// printf("copy_string\n");
// 			result = copy_string(line, &i, NULL);
// 		}
// 		else if (line[i] && line[i] == '"')
// 		{
// 			i++;
// 			// printf("expand_dbl_quote\n");
// 			result = expand_dbl_quote(line, &i, msh);
// 			i++;
// 		}
// 		else
// 			i++;
// 	}
// 	if (result == NULL)
// 	{
// 		i = 0;
// 		result = malloc(sizeof(char) * (ft_strlen(line) + 1));
// 		if (result != NULL)
// 			ft_strlcpy(result, line, ft_strlen(line) + 1);
// 	}
// 	// free (line);
// 	return (result);
// }
