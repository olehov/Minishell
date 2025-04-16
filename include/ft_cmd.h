/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:42:05 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 11:22:55 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_H
# define FT_CMD_H

# include "../ft_libft/headers/libft.h"
# include "ft_minishell_types.h"

/**
 * @brief Initializes a new command node with default values.
 * 
 * @return Pointer to a newly allocated t_cmd structure.
 */
t_cmd	*init_cmd_node(void);

/**
 * @brief Adds a redirection to the command's redirection list.
 * 
 * @param cmd Pointer to the command node.
 * @param type Type of redirection (e.g., input, output, append).
 * @param path Path to the file for redirection.
 */
void	add_redirection(t_cmd *cmd, t_redirect_type type, char *path);

/**
 * @brief Parses all commands from tokenized input and constructs command list.
 * 
 * @param msh Pointer to main shell structure.
 * @return Pointer to the head of the command list.
 */
t_cmd	*get_cmd_lst(t_minish *msh);

/**
 * @brief Frees memory allocated for a single command node.
 * 
 * @param cmd Pointer to the command node to be freed.
 */
void	free_cmd_node(t_cmd *cmd);

/**
 * @brief Frees an entire linked list of command nodes.
 * 
 * @param cmd Double pointer to the head of the command list.
 */
void	free_cmd_list(t_cmd **cmd);

/**
 * @brief Wraps part of a string with quotes, e.g., for heredoc delimiters.
 * 
 * @param input Input string.
 * @param start Start index of the part to quote.
 * @param end End index of the part to quote.
 * @return Newly allocated string with quoted part.
 */
char	*insert_quotes_around_delim(char *input, size_t start, size_t end);

/**
 * @brief Finds the bounds of a heredoc delimiter in the input.
 * 
 * @param input The full input line.
 * @param start Pointer to store the start index.
 * @param end Pointer to store the end index.
 */
void	find_delimiter_bounds(char *input, size_t *start, size_t *end);

/**
 * @brief Processes redirection tokens and updates the command structure.
 * 
 * @param i Pointer to the current index in the token list.
 * @param cmd Pointer to the command node.
 * @param tokens Array of parsed tokens.
 * @return true if successful, false otherwise.
 */
bool	handle_redirects(int *i, t_cmd *cmd, t_token *tokens);

/**
 * @brief Parses a single command from a set of tokens.
 * 
 * @param tokens Array of tokens.
 * @param msh Pointer to main shell structure.
 * @return Newly created command node representing a single command.
 */
t_cmd	*parse_single_command_from_tokens(t_token *tokens, t_minish *msh);

/**
 * @brief Handles quoting of heredoc delimiters, considering edge cases.
 * 
 * @param result Pointer to the heredoc line to modify.
 * @param i Pointer to the current index.
 * @return 0 on success, non-zero on error.
 */
int		handle_heredoc_quote(char **result, size_t *i);

/**
 * @brief Applies environment variable expansion and quoting to a token.
 * 
 * @param env_applied The value after env expansion.
 * @param tokens Array of tokens.
 * @param i Index of the current token.
 * @return Newly allocated string after processing.
 */
char	*get_processed(char *env_applied, t_token *tokens, int i);

/**
 * @brief Top-level parser that processes raw input and returns a command list.
 * 
 * @param input Raw input string from the user.
 * @param env Environment variable list.
 * @param msh Pointer to shell state.
 * @return Pointer to the parsed command list.
 */
t_cmd	*parse_input(char *input, t_list *env, t_minish *msh);

#endif