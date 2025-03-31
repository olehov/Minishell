/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:30:58 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/29 14:41:24 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ===== Видалення лапок з рядка =====
char	*remove_quotes(char *str)
{
	int		i = 0;
	int		j = 0;
	char	quote = 0;
	char	*res = malloc(ft_strlen(str) + 1);
	if (!res) return NULL;

	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i]; // початок лапок
		else if (quote && str[i] == quote)
			quote = 0; // кінець лапок
		else
			res[j++] = str[i]; // копіюємо символ
		i++;
	}
	res[j] = '\0';
	return (res);
}

// ===== Додавання аргументу в масив =====
void add_arg(t_cmd *cmd, char *arg)
{
	int i = 0;
	char **new_args;

	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		cmd->args[0] = arg;
		cmd->args[1] = NULL;
		return ;
	}
	while (cmd->args[i]) i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	for (int j = 0; j < i; j++) new_args[j] = cmd->args[j];
	new_args[i] = arg;
	new_args[i + 1] = NULL;
	if (cmd->args != NULL)
		free(cmd->args);
	cmd->args = new_args;
}

// ===== Обробка редіректів для команди =====
void	handle_redirects(t_cmd *cmd)
{
	if (cmd->outfile)
	{
		if (cmd->append_out)
			append_to_file(cmd->infile, cmd->outfile, O_RDWR | O_APPEND);
		else
			append_to_file(cmd->infile, cmd->outfile, O_RDWR | O_TRUNC);
	}
	if (cmd->infile)
	{
		if (cmd->redirect_in)
		{
			append_to_file(cmd->outfile, cmd->infile,
				O_RDONLY | O_CREAT | O_TRUNC);
		}
	}
}

// ===== Перевірка для echo -n (чи лише n) =====
int only_n(char *str)
{
	int i = 1;
	if (str[0] != '-') return 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}
