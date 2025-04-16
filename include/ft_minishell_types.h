/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_types.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:14:36 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:44:48 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_TYPES_H
# define FT_MINISHELL_TYPES_H

# include <unistd.h>
# include <sys/types.h>
# include <stdbool.h>
# include <signal.h>
# include <signal.h>
# include "../ft_libft/headers/libft.h"

# define RED "\001\033[31m\002"
# define CYAN "\001\033[36m\002"
# define GRN "\001\033[32m\002"
# define RESET "\001\033[0m\002"

# define PERMISSION_DENIED	127
# define IS_A_DIRECTORY	126
# define RED "\001\033[31m\002"
# define CYAN "\001\033[36m\002"
# define GRN "\001\033[32m\002"
# define RESET "\001\033[0m\002"

# define PERMISSION_DENIED	127
# define IS_A_DIRECTORY	126

typedef struct s_heredoc
{
	char	*filename;
	char	*delimiter;
}	t_heredoc;

typedef struct s_tokenizer_ctx
{
	char	*accum;
	int		i;
	int		j;
	int		in_quotes;
	char	quote_char;
	int		skip_next_token_quote_handling;
}	t_tokenizer_ctx;

typedef struct s_tokenizer_ctx
{
	char	*accum;
	int		i;
	int		j;
	int		in_quotes;
	char	quote_char;
	int		skip_next_token_quote_handling;
}	t_tokenizer_ctx;

typedef struct s_token
{
	char	*value;
	bool	in_quotes;
	char	quote_char;
}	t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/**
 * @param _redirect_in <
 * @param _redirect_out >
 * @param _heredoc <<
 * @param _append_to_file >>
 */
typedef enum e_redirect_type
{
	_reset = 0,
	_redirect_in = 1,
	_redirect_out = 2,
	_heredoc = 3,
	_append_to_file = 4
}	t_redirect_type;

/**
 * @param filename - pointer to name of file
 * @param type - type of reddirection
 */
typedef struct s_redirect
{
	char			*filename;
	t_redirect_type	type;
}	t_redirect;

typedef struct s_cmd
{
	pid_t			pid;
	char			*infile;
	char			*outfile;
	char			**args;
	int				pipe_fd[2];
	t_list			*redirect_lst;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minish
{
	t_list	*env;
	t_list	*heredocs;
	t_cmd	*cmd;
	t_token	*tokens;
	char	**pipe_split;
	int		exit_code;
	t_token	*tokens;
	char	**pipe_split;
	int		exit_code;
}	t_minish;

#endif