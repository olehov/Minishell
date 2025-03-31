/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:48:03 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/29 14:25:36 by ogrativ          ###   ########.fr       */
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
	return (cmd);
}

void	parse_redirects(t_cmd *cmd, char **tokens, int *i)
{
	if (!tokens[*i + 1])
		return ;
	if (ft_strcmp(tokens[*i], "<") == 0)
	{
		cmd->infile = ft_strdup(tokens[++(*i)]);
		cmd->redirect_in = 1;
		add_arg(cmd, ft_strdup(tokens[*i]));
	}
	else if (ft_strcmp(tokens[*i], ">") == 0)
	{
		cmd->outfile = ft_strdup(tokens[++(*i)]);
		cmd->append_out = 0;
	}
	else if (ft_strcmp(tokens[*i], ">>") == 0)
	{
		cmd->outfile = ft_strdup(tokens[++(*i)]);
		cmd->append_out = 1;
	}
	else if (ft_strcmp(tokens[*i], "<<") == 0)
	{
		cmd->infile = ft_strdup(tokens[(*i)++]);
		add_arg(cmd, ft_strdup(HEREDOC_FILENAME_PATH));
		cmd->delimiter = ft_strdup(tokens[*i]);
	}
}

//Parsing arguments with quote handling and $VAR
char	**split_args_handling_quotes(char *input, t_minish *msh)
{
	char	*expanded;
	char	*cleaned;
	char	**tokens;
	int		i;

	i = 0;
	expanded = process_env(input, msh->env);
	if (expanded == NULL)
	{
		perror("expanded is NULL\n");
		return (NULL);
	}
	tokens = ft_split(expanded, ' ');
	while (tokens && tokens[i])
	{
		cleaned = remove_quotes(tokens[i]);
		if (tokens[i] != NULL)
			free(tokens[i]);
		tokens[i] = cleaned;
		i++;
	}
	free(expanded);
	return (tokens);
}

// Parsing a single command (between pipes)
t_cmd	*parse_single_command(char *command, t_minish *msh)
{
	char	**tokens;
	t_cmd	*cmd;
	int		i;

	tokens = split_args_handling_quotes(command, msh);
	if (tokens == NULL)
		return (NULL);
	cmd = init_cmd_node();
	if (cmd == NULL)
		return (free_split(tokens), NULL);
	i = -1;
	while (tokens[++i] != NULL)
	{
		if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], ">>") || !ft_strcmp(tokens[i], "<<"))
			parse_redirects(cmd, tokens, &i);
		else
			add_arg(cmd, ft_strdup(tokens[i]));
	}
	return (free_split(tokens), cmd);
}

// Основний парсинг всієї лінії (з пайпами)
t_cmd	*parse_input(char *input, t_list *env)
{
	t_cmd	*first;
	t_cmd	*last;
	t_cmd	*cmd;
	char	**pipe_split;
	int		i;

	(void)env;
	first = NULL;
	last = NULL;
	i = 0;
	pipe_split = ft_split(input, '|');
	while (pipe_split[i] != NULL)
	{
		cmd = parse_single_command(pipe_split[i], &g_minish);
		if (!first)
			first = cmd;
		else
			last->next = cmd;
		last = cmd;
		i++;
	}
	free_split(pipe_split);
	return (first);
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
