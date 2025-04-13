/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:33:32 by marta             #+#    #+#             */
/*   Updated: 2025/04/13 23:03:55 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(char **args, t_minish *msh, bool is_child)
{

    if (args[1] && args[2])
    {
        ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
        msh->exit_code = 1;
        return ;
    }
    if (args[1])
    {
        if (!ft_isdigit(args[1][0]) && args[1][0] != '-')
            ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
        else
            msh->exit_code = ft_atoi(args[1]);
    }
    else
        msh->exit_code = 0;
    if (!is_child)
    {
        msh->should_exit = 1; // true
    }
}
