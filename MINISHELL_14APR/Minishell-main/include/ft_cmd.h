/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfedorys <mfedorys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:42:05 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 20:03:22 by mfedorys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_H
# define FT_CMD_H

# include "../ft_libft/headers/libft.h"
# include "ft_minishell_types.h"
// # include "./minishell.h"

t_cmd	*init_cmd_node(void);

/**
 * @param cmd Pointer to current cmd node
 * @param type Redirection type from e_redirectind_type enum
 */
void	add_redirection(t_cmd *cmd, t_redirect_type type, char *path);

t_cmd	*get_cmd_lst(t_minish *msh);

void	free_cmd_node(t_cmd *cmd);
void	free_cmd_list(t_cmd **cmd);
char	*insert_quotes_around_delim(char *input, size_t start, size_t end);
void	find_delimiter_bounds(char *input, size_t *start, size_t *end);
bool	handle_redirects(int *i, t_cmd *cmd, t_token *tokens);
t_cmd	*parse_single_command_from_tokens(t_token *tokens, t_minish *msh);
void	init_quote_state(char c, int *in_quote, char *quote);
int		handle_heredoc_quote(char **result, size_t *i);
void	process_argument_token(t_token *tokens, t_cmd *cmd, t_minish *msh,
			int *i);
char	*get_processed(char *env_applied, t_token *tokens, int i);
t_cmd	*parse_input(char *input, t_list *env, t_minish *msh);

#endif