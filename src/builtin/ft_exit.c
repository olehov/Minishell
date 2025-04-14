/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:19:51 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 16:09:45 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdint.h>

void	clear_data(t_minish *msh)
{
	rl_clear_history();
	free_cmd_list(msh->cmd);
	free_shell(msh);
}

static bool	is_only_digit(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static bool	is_min_max_long(char *str)
{
	char	*long_max;
	char	*long_min;
	size_t	len;
	int		res;

	if (str == NULL)
		return (true);
	res = 0;
	len = ft_strlen(str);
	if (len > 11)
		return (false);
	if ((len == 10 || len == 11) && (str[0] == '+' || ft_isdigit(str[0])))
	{
		if (len == 11 && str[0] != '+')
			return (false);
		long_max = ft_ltoa(LONG_MAX);
		if (str[0] == '+')
			res = ft_strcmp(str + 1, long_max);
		else
			res = ft_strcmp(str, long_max);
		free(long_max);
	}
	else if ((len == 10 || len == 11) && (str[0] == '-' || ft_isdigit(str[0])))
	{
		if (len == 11 && str[0] != '-')
			return (false);
		long_min = ft_ltoa(LONG_MIN);
		res = ft_strcmp(str, long_min);
		free(long_min);
	}
	else
		return (true);
	return (res <= 0);
}

static int	parce_exit_code(char *str)
{
	int	exit_code;

	exit_code = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	exit_code = ft_atol(str);
	return ((unsigned char)exit_code);
}

int	ft_exit(char **args, t_minish *msh, bool is_child)
{
	long	exit_code;

	if (args == NULL || *args == NULL)
		return (-1);
	if (is_child == false)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (get_row_size(args) > 2 && is_only_digit(args[1]))
	{
		if (is_child == 1)
			clear_data(msh);
		ft_putendl_fd(" too many arguments", STDERR_FILENO);
		return (-1);
	}
	else if ((get_row_size(args) >= 2 && is_only_digit(args[1]) == 0)
		|| !is_min_max_long(args[1]))
	{
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		clear_data(msh);
		exit(2);
	}
	exit_code = parce_exit_code(args[1]);
	clear_data(msh);
	exit(exit_code);
}
