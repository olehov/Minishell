/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 09:56:58 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:53:40 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../ft_libft/headers/libft.h"
# include "ft_heredoc.h"
# include "ft_redirection.h"
# include "ft_cmd.h"
# include "ft_minishell_types.h"
# include "ft_signals.h"
# include "ft_builtin.h"
# include "ft_env.h"
# include "ft_parser.h"
# include "ft_utils.h"

/** SHELL **/
void	init_shell(t_minish *msh, char **envp);
char	*get_line(t_minish *msh);
void	clear_data(t_minish *msh);
void	free_shell(t_minish *msh);

/** EXECUTION **/
void	execute_commands(t_minish *msh);
void	execute_builtin(t_cmd *cmd, t_minish *msh);
void	launch_child(t_cmd *cmd, t_minish *msh);
void	add_arg(t_cmd *cmd, char *arg);
void	close_all_pipes(t_cmd *cmd);
void	set_pipe_fds(t_cmd *cmd, t_minish *msh);

#endif