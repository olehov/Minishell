/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 09:56:58 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/23 15:07:34 by ogrativ          ###   ########.fr       */
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

// ----------------------
//     GLOBAL VARIABLES
// ----------------------

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	char			*delimiter;
	int				append_out;
	int				pipe_fd[2];
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minish
{
	t_list	*env;
	int		last_exit_code;
}	t_minish;

extern t_minish	g_minish;

# define HEREDOC_FILENAME_PATH "/tmp/heredoc_tmp.txt"

# define ANSI_CLEAR_SCREEN "\033[H\033[J"

# define RED "\033[31m"
# define CYAN "\033[36m"
# define RESET "\033[0m"
# define GRN "\033[32m"

// ----------------------
//       FUNCTIONS
// ----------------------

// ===== main.c =====
void	init_shell(t_list **env, char **envp);
void	signal_handler(int signo);

// ===== parse_input.c =====
t_cmd	*parse_input(char *input, t_list *env);
void	free_cmd_list(t_cmd *cmd);

// ===== execute_commands.c =====
void	execute_commands(t_cmd *cmd_list, t_minish *msh);
void	handle_redirects(t_cmd *cmd);
int		is_builtin(char *cmd);
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

// ===== heredoc.c =====
int		ft_heredoc(char *delimiter, t_list *env);

// ===== utils.c =====
char	*remove_quotes(char *str);
void	add_arg(t_cmd *cmd, char *arg);
char	**split_path(t_list *lst, char *key, char c);

// ===== env management (твій готовий функціонал) =====
int		init_env(t_list **lst, char *env[]);
t_env	*ft_get_env(t_list *lst, char *key);
char	*get_env_value(const char *var_name, t_list *lst);
char	**env_list_to_str_arr(t_list *lst);
void	ft_env_unset(t_list **lst, char *env);
int		ft_set_env(t_list **lst, char *env);
void	print_env_list(t_list *lst);

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