/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 09:56:58 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:46 by ogrativ          ###   ########.fr       */
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

// ----------------------
//       FUNCTIONS
// ----------------------

void	free_tokens(t_token *tokens);
int		parce_heredoc(t_minish *msh, int *i, t_cmd *cmd);
int		handle_word(char *input, int *i, char **accum);
int		handle_single_redirect(char *input,
			t_token *tokens, t_tokenizer_ctx *ctx);
bool	is_only_digit(char *str);
char	*get_line(t_minish *msh);
char	*get_prompt(t_minish *msh);
void	clear_data(t_minish *msh);
void	free_shell(t_minish *msh);
void	heredoc_signal_handler(int signo);
size_t	get_row_size(char **args);
bool	ft_is_directory(const char *path);
bool	is_closed_quote(char quote, int start, char *str);

int		is_builtin(char **cmd);
char	**split_outside_quotes(char *input, char delimiter);

// ===== main.c =====
void	init_shell(t_minish *msh, char **envp);
void	signal_handler(int signo);

// ===== parse_input.c =====
t_cmd	*parse_input(char *input, t_list *env, t_minish *msh);
char	**split_outside_quotes(char *input, char delimiter);
char	*remove_outer_quotes(char *str);

int		handle_double_redirect(char *input,
			t_token *tokens, t_tokenizer_ctx *ctx);
void	handle_quote(char *input, t_tokenizer_ctx *ctx);
char	*append_part(char *accum, char *part);
void	reset_quote_state(t_tokenizer_ctx *ctx);
void	set_token(t_token *token, t_tokenizer_ctx *ctx);
t_token	*tokenize_with_quote_info(char *input);

// ===== execute_commands.c =====
void	execute_commands(t_minish *msh);
int		is_builtin(char **cmd);
void	execute_builtin(t_cmd *cmd, t_minish *msh);

// ===== builtin_echo.c =====

/**
 * @name ft_echo - display a line of text
 *
 * @brief Mimics the behavior of the shell built-in `echo` command.
 *        Supports multiple `-n` options to suppress the trailing newline.
 *
 * @param args Null-terminated array of strings to print. If one or more
 *             `-n` options are passed at the beginning, the final newline
 *             character is omitted.
 *
 * @return 0 on success, -1 on error (e.g., if args is NULL)
 * 
 * @note Consecutive `-n` flags (e.g., `-n -n`) are supported,
 * following bash behavior.
 */
int		ft_echo(char **args);

// ===== builtin_utils.c =====
int		ft_cd(char *path, t_list **lst);
int		printpwd(void);
void	print_env_list(t_list *lst);
int		ft_set_env(t_list **lst, char *env);
void	ft_env_unset(t_list **lst, char *env);

/**
 * @brief ft_exit doing clean exit from program if is_child equal false.
 * If is_child equal true just use ft_exit for exit from child proccess.
 * Function should change msh->exit_code to code from args[1] or add own
 * exit code if args more than 2 or args[1] not integer type
 * 
 * @param args args[0]= "exit"
 * @param msh pointer to main minishell structure
 * @param is_child if is_child true do exit without clear all data
 */
int		ft_exit(char **args, t_minish *msh, bool is_child);

void	execute_builtin(t_cmd *cmd, t_minish *msh);

void	launch_child(t_cmd *cmd, t_minish *msh);

int		ft_decode_wstatus(int wstatus);

// ===== utils =====
char	*remove_quotes(char *str);
void	add_arg(t_cmd *cmd, char *arg);
char	**split_path(t_list *lst, char *key, char c);
void	close_all_pipes(t_cmd *cmd);
void	set_pipe_fds(t_cmd *cmd, t_minish *msh);

// ===== env management (твій готовий функціонал) =====
int		init_env(t_list **lst, char *env[]);
t_env	*ft_get_env(t_list *lst, char *key);
char	*get_env_value(const char *var_name, t_list *lst);
char	**env_list_to_str_arr(t_list *lst);

// ===== process_env & expand (твій код) =====
char	*process_env(const char *input, t_list *lst, t_minish *msh);
char	*expand_line(char *line, t_minish *msh, int i);

// ===== other env/utils (твій код) =====
t_env	*parce_env(char *env);
void	free_env(void *env);
t_list	*ft_get_env_node(t_list *lst, char *key);

void	free_split(char **str);

#endif