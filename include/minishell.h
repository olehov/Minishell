/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 09:56:58 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 13:20:41 by ogrativ          ###   ########.fr       */
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
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../ft_libft/headers/libft.h"
# include "ft_heredoc.h"
# include "ft_redirection.h"
# include "ft_cmd.h"
# include "ft_minishell_types.h"

// ----------------------
//     GLOBAL VARIABLES
// ----------------------

extern	int	g_last_exit_code;

// ----------------------
//       FUNCTIONS
// ----------------------

size_t	get_row_size(char **args);
void	print_cd_error(void);
int		is_directory(const char *path);
void	print_args(char	**args);

char	**split_outside_quotes(char *input, char delimiter);

// ===== main.c =====
void	init_shell(t_minish *msh, char **envp);
void	signal_handler(int signo);

// ===== parse_input.c =====
t_cmd	*parse_input(char *input, t_list *env, t_minish *msh);
// void	free_cmd_node(t_cmd *cmd);
// void	free_cmd_list(t_cmd *cmd);

// ===== execute_commands.c =====
void	execute_commands(t_minish *msh);
int		is_builtin(char **cmd);
void	execute_builtin(t_cmd *cmd, t_minish *msh);

// ===== builtin_echo.c =====
void	ft_echo(char **args);
int		only_n(char *str);

// ===== builtin_utils.c =====
int		ft_cd(char *path, t_list **lst);
int		printpwd(void);
void	print_env_list(t_list *lst);
int		ft_set_env(t_list **lst, char *env);
void	ft_env_unset(t_list **lst, char *env);
void	ft_exit(char **args);

int	append_to_file(char *inputFileName, char *outputFileName, int flags);

// ===== utils.c =====
char	*remove_quotes(char *str);
void	add_arg(t_cmd *cmd, char *arg);
char	**split_path(t_list *lst, char *key, char c);

// ===== env management (твій готовий функціонал) =====
int		init_env(t_list **lst, char *env[]);
t_env	*ft_get_env(t_list *lst, char *key);
char	*get_env_value(const char *var_name, t_list *lst);
char	**env_list_to_str_arr(t_list *lst);

// ===== process_env & expand (твій код) =====
char	*process_env(const char *input, t_list *lst);
char	*expand_line(char *line, t_minish *msh, int i);

// ===== other env/utils (твій код) =====
t_env	*parce_env(char *env);
void	free_env(void *env);
t_list	*ft_get_env_node(t_list *lst, char *key);

// ===== other helpers =====
void	print_file_error(void); // з print_file_error.c

void	free_split(char **str);

#endif