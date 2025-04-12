/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:05:11 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/12 19:57:52 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_heredoc.h"

void	heredoc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		exit(130); // 128 + SIGINT
	}
	else if (signo == SIGQUIT)
	{
		exit(131); // 128 + SIGQUIT
	}
}


static bool	check_delimiter(const char *delimiter)
{
	if (delimiter == NULL || delimiter[0] == '\0')
	{
		errno = EINVAL;
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}

static char	*allocate_delimitter(char *delimiter)
{
	char	*tmp;

	if (check_delimiter(delimiter) == 0)
		return (NULL);
	tmp = ft_calloc(sizeof(char *), ft_strlen(delimiter));
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	*get_delimiter_without_quotes(char *delimiter, bool *in_quotes)
{
	char	*tmp;
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = allocate_delimitter(delimiter);
	if (tmp == NULL)
		return (NULL);
	while (delimiter[i] != '\0')
	{
		if (delimiter[i] == '\'' || delimiter[i] == '\"')
		{
			*in_quotes = true;
			quote = delimiter[i++];
			while (delimiter[i] != quote && delimiter[i] != '\0')
				tmp[j++] = delimiter[i++];
		}
		else
			tmp[j++] = delimiter[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

static int	read_line(int fd, char *delimiter, t_list *env, bool in_quotes)
{
	char	*buffer;
	char	*tmp;

	if (isatty(STDIN_FILENO))
		buffer = readline("> ");
	else
		buffer = readline(NULL);
	if (buffer == NULL)
	{
		ft_putstr_fd(" here-document delimited by end-of-file ",
			STDERR_FILENO);
		ft_putstr_fd("(wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("\')\n", STDERR_FILENO);
		exit (0);
	}
	if (ft_strcmp(buffer, delimiter) == 0)
	{
		return (free(buffer), 0);
	}
	if (in_quotes == false)
	{
		tmp = process_env(buffer, env);
		ft_putendl_fd(tmp, fd);
		free(tmp);
	}
	else
		ft_putendl_fd(buffer, fd);
	free(buffer);
	return (1);
}

void	run_heredoc(t_heredoc *heredoc, t_list *env)
{
	int		fd;
	int		exit_status;
	bool	in_quotes;
	char	*del_without_quotes;

	in_quotes = false;
	exit_status = 1;
	if (check_delimiter(heredoc->delimiter) == 0)
		exit(1);
	fd = open(heredoc->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	del_without_quotes = get_delimiter_without_quotes(heredoc->delimiter,
			&in_quotes);
	while (exit_status != -1 && exit_status != 0)
		exit_status = read_line(fd, del_without_quotes, env, in_quotes);
	close(fd);
	free(del_without_quotes);
	exit(0);
}

int	ft_heredoc(t_heredoc *heredoc, t_list *env)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signal_handler);
		// signal(SIGQUIT, SIG_IGN);
		run_heredoc(heredoc, env);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, signal_handler);
		g_last_exit_code = ft_decode_wstatus(status);
		if (g_last_exit_code != 0)
			return (-1);
	}
	return (0);
}


// int	ft_heredoc(t_heredoc *heredoc, t_list *env)
// {
// 	int		fd;
// 	int		exit_status;
// 	bool	in_quotes;
// 	char	*del_without_quotes;
// 	int		status;
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, heredoc_signal_handler);
// 		in_quotes = false;
// 		exit_status = 1;
// 		if (check_delimiter(heredoc->delimiter) == 0)
// 			exit(1);
// 		fd = open(heredoc->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 		if (fd < 0)
// 			exit(1);
// 		del_without_quotes = get_delimiter_without_quotes(heredoc->delimiter,
// 				&in_quotes);
// 		while (exit_status != -1 && exit_status != 0)
// 			exit_status = read_line(fd, del_without_quotes, env, in_quotes);
// 		close(fd);
// 		free(del_without_quotes);
// 		exit(0);
// 	}
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN); // тимчасово ігноруємо Ctrl+C
// 		waitpid(pid, &status, 0);
// 		signal(SIGINT, signal_handler);
// 		g_last_exit_code = ft_decode_wstatus(status);
// 		if (g_last_exit_code != 0)
// 			return (-1);
// 	}
// 	return (0);
// }
