/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dbl_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:01:57 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 17:29:40 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*copy_first_str(char *prev, char *start, char *end)
{
	int		i;
	char	*new;
	char	*res;

	i = 0;
	while (start + i != end)
		i++;
	new = malloc(i + 1);
	i = 0;
	while (start + i != end)
	{
		new[i] = start[i];
		i++;
	}
	new[i] = '\0';
	res = ft_strjoin(prev, new);
	if (prev != NULL)
		free(prev);
	free(new);
	return (res);
}

static void	skip_key(char *line, int *i)
{
	while ((ft_isalnum(line[*i]) || line[*i] == '_')
		&& line[*i] != '\0' && line[*i] != '"' && !ft_isblank(line[*i]))
		(*i)++;
}

char	*find_key(char *key_start)
{
	int		k;
	char	*ret;

	k = 0;
	while ((ft_isalnum(key_start[k]) || key_start[k] == '_')
		&& key_start[k] && key_start[k] != '"' && !ft_isblank(key_start[k]))
		k++;
	ret = malloc (k + 1);
	k = 0;
	while ((ft_isalnum(key_start[k]) || key_start[k] == '_')
		&& key_start[k] && key_start[k] != '"' && !ft_isblank(key_start[k]))
	{
		ret[k] = key_start[k];
		k++;
	}
	ret[k] = '\0';
	return (ret);
}

static char	*get_copy_str(char *result, char *str1, char *end, int i)
{
	if (!str1 && i > 1)
		str1 = copy_first_str(NULL, end, end + i);
	else if (i > 1)
		str1 = copy_first_str(result, str1, end + i);
	return (str1);
}

char	*expand_dbl_quote(char *line, int *i, t_minish *msh)
{
	char	*result;
	char	*str1;
	char	*str2;

	str1 = NULL;
	while (line[*i] != '"' && line[*i] != '\0')
	{
		if (line[*i] == '$')
		{
			str1 = get_copy_str(result, str1, line, *i);
			str2 = get_env_value(find_key(line + *i + 1), msh->env);
			result = ft_strjoin(str1, str2);
			free(str1);
			str1 = NULL;
			free(str2);
			skip_key(line, i);
			if (line[*i] != '"')
				str1 = line + *i;
		}
		else
			(*i)++;
	}
	return (result);
}
