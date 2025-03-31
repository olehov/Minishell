/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:42:26 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/28 10:30:08 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	close_file(int fd)
{
	if (fd >= 0)
	{
		close(fd);
	}
}

int	append_to_file(char *inputFileName, char *outputFileName, int flags)
{
	int	input_fd;
	int	output_fd;

	if (inputFileName != NULL && ft_strrchr(inputFileName, '.')[0] != '.')
	{
		input_fd = open(inputFileName, O_RDONLY);
		if (input_fd < 0)
		{
			return (perror("Can't open input file:"), -1);
		}
		dup2(input_fd, STDIN_FILENO);
	}
	if (access(inputFileName, F_OK) == 0)
		output_fd = open(outputFileName, flags);
	else
		output_fd = open(outputFileName, flags | O_CREAT, 0644);
	// perror(strerror(errno));
	if (output_fd < 0)
	{
		close(input_fd);
		return (perror("Can't open output file:"), -1);
	}
	dup2(output_fd, STDOUT_FILENO);
	close_file(input_fd);
	close_file(output_fd);
	return (0);
}
