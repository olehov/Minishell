/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:42:26 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/04 17:37:17 by ogrativ          ###   ########.fr       */
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

int	append_to_file(int input_fd, char *outputfilename)
{
	int		output_fd;
	char	*line;

	if (outputfilename == NULL)
	{
		errno = EINVAL;
		return (print_file_error(), -1);
	}
	output_fd = open(outputfilename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (input_fd < 0 || output_fd < 0)
		return (print_file_error(), close_file(output_fd), -1);
	while (true)
	{
		line = get_next_line(input_fd);
		if (line == NULL)
			break ;
		ft_putstr_fd(line, output_fd);
		free(line);
	}
	close(output_fd);
	return (0);
}
