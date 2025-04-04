/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:13:48 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/04 11:40:34 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_err(char *text, int __errnum)
{
	perror(text);
	strerror(__errnum);
}

void	print_file_error(void)
{
	if (errno == ENOENT)
		print_err("Open failed: File does not exist", errno);
	else if (errno == EEXIST)
		perror("File already exists\n");
	else if (errno == ENOTDIR)
		perror("A component of the path is not a directory\n");
	else if (errno == EISDIR)
		perror("Expected a file, but it's a directory\n");
	else if (errno == EMFILE)
		perror("Too many open files in the process\n");
	else if (errno == ENFILE)
		perror("Too many open files in the system\n");
	else if (errno == ELOOP)
		perror("Too many symbolic links encountered\n");
	else if (errno == EACCES)
		print_err("Open failed", errno);
	else
		strerror(errno);
}
