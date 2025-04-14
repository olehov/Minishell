/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:50:46 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 11:08:16 by ogrativ          ###   ########.fr       */
/*   Updated: 2025/04/13 22:57:18 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	printerrcode(t_minish *msh)
{
	char	*exit_code;

	exit_code = ft_itoa(msh->exit_code);
	if (msh != NULL && exit_code != NULL)
	{
		perror(exit_code);
	}
	free(exit_code);
}

int	run_cd(t_cmd *cmd, t_minish *msh)
{
	if (get_row_size(cmd->args) > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	else
		return (ft_cd(cmd->args[1], &msh->env));
}

// // --- Вбудовані команди ---
void	execute_builtin(t_cmd *cmd, t_minish *msh)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		exit_code = run_cd(cmd, msh);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exit_code = printpwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		print_env_list(msh->env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		exit_code = ft_set_env(&msh->env, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_env_unset(&msh->env, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		exit_code = ft_echo(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "$?") == 0)
		printerrcode(msh);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd->args, msh, 0);
	if (exit_code == -1)
		msh->exit_code = EXIT_FAILURE;
	else
		msh->exit_code = EXIT_SUCCESS;
}
