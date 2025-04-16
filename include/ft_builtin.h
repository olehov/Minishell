/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:05:07 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:58:37 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include "ft_minishell_types.h"
# include "ft_heredoc.h"
# include "ft_env.h"

/**
 * @brief Prints arguments to stdout (like echo), handles -n option.
 */
int		ft_echo(char **args);

/**
 * @brief Changes the current working directory.
 */
int		ft_cd(char *path, t_list **lst);

/**
 * @brief Prints the current working directory.
 */
int		printpwd(void);

/**
 * @brief Exits the shell with a specified code.
 * 
 * @param args Arguments passed to exit (e.g., numeric code).
 * @param msh Shell state for cleanup.
 * @param is_child Indicates if executed from a child process.
 * @return Exit code to pass to shell.
 */
int		ft_exit(char **args, t_minish *msh, bool is_child);

/**
 * @brief Checks if a command is a shell built-in.
 * 
 * @param cmd Command and arguments array.
 * @return ID for built-in if matched, 0 otherwise.
 */
int		is_builtin(char **cmd);

#endif