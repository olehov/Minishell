/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:45:35 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 00:21:51 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/ft_cmd.h"

char	*get_line(t_minish *msh)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(msh);
	if (isatty(STDIN_FILENO))
	{
		if (prompt == NULL)
			line = readline(GRN "minishell> " RESET);
		else
			line = readline(prompt);
	}
	else
		line = get_next_line(STDIN_FILENO);
	if (line == NULL)
	{
		if (prompt != NULL)
			free(prompt);
		return (NULL);
	}
	if (prompt != NULL)
		free(prompt);
	return (line);
}

// char	*get_line(t_minish *msh)
// {
// 	char	*line;
// 	char	*prompt;

// 	prompt = get_prompt(msh);
// 	if (isatty(STDIN_FILENO))
// 	{
// 		if (prompt == NULL)
// 			line = readline(GRN "minishell> " RESET);
// 		else
// 			line = readline(prompt);
// 	}
// 	else
// 		line = readline("minishell> ");
// 	if (line == NULL)
// 	{
// 		if (prompt != NULL)
// 			free(prompt);
// 		return (NULL);
// 	}
// 	if (prompt != NULL)
// 		free(prompt);
// 	return (line);
// }

t_cmd	*get_cmd_lst(t_minish *msh)
{
	char	*line;
	t_cmd	*cmd_list;

	line = get_line(msh);
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	cmd_list = parse_input(line, msh->env, msh);
	free(line);
	return (cmd_list);
}
