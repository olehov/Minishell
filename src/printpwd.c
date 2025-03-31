/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:41:35 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/29 21:38:42 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <linux/limits.h>

int	printpwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		if (errno == EINVAL)
			return (perror("printpwd: some arg is null"), -1);
		else if (errno == ENOMEM)
			return (perror("printpwd:"), -1);
		else if (errno == ERANGE)
			return (perror("printpwd: buffer to small"), -1);
	}
	printf("%s\n", pwd);
	return (0);
}
