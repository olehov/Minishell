/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:41:35 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/13 23:06:42 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#ifdef __linux__
#include <linux/limits.h>
#else
#include <limits.h>
#endif

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
