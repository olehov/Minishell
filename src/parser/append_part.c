/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 06:16:17 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 06:18:42 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"

static char	*process_part(char *part, t_minish *msh, bool *is_removed)
{
	char	*processed;

	*is_removed = false;
	if (part[0] == '\'')
	{
		*is_removed = true;
		processed = remove_outer_quotes(part);
	}
	else
		processed = process_env(part, msh->env, msh, 0);
	return (processed);
}

static char	*clean_processed(char *processed, bool is_removed)
{
	char	*cleaned;

	if (!processed)
		return (NULL);
	if (is_removed)
		return (processed);
	cleaned = remove_quotes(processed);
	free(processed);
	return (cleaned);
}

static char	*join_parts(char *accum, char *processed)
{
	char	*tmp;
	char	*joined;

	tmp = NULL;
	joined = NULL;
	if (accum)
	{
		tmp = ft_strdup(accum);
		free(accum);
		joined = ft_strjoin(tmp, processed);
		free(tmp);
	}
	else
		joined = ft_strdup(processed);
	free(processed);
	return (joined);
}

char	*append_part(char *accum, char *part, t_minish *msh)
{
	char	*processed;
	bool	is_removed;

	processed = process_part(part, msh, &is_removed);
	processed = clean_processed(processed, is_removed);
	return (join_parts(accum, processed));
}
