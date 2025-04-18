/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:03:31 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 03:41:45 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_minishell_types.h"
# include "ft_env.h"
# include "ft_heredoc.h"
# include "ft_redirection.h"
# include "ft_signals.h"
# include "ft_utils.h"

/**
 * @brief Parses raw input and returns the top-level command list.
 * 
 * @param input Raw input string from user.
 * @param env Environment list.
 * @param msh Pointer to the shell structure.
 * @return Linked list of parsed command structures.
 */
t_cmd	*parse_input(char *input, t_list *env, t_minish *msh);

/**
 * @brief Tokenizes input, tracking quoting context for each token.
 * 
 * @param input Input line to tokenize.
 * @param msh Pointer to shell structure (used for error handling).
 * @return Array of tokens with quote metadata.
 */
t_token	*tokenize_with_quote_info(char *input, t_minish *msh);

/**
 * @brief Removes outer quotes from a string, if present.
 * 
 * @param str Input string with optional quotes.
 * @return Newly allocated string without outer quotes.
 */
char	*remove_outer_quotes(char *str);

/**
 * @brief Handles quote context during tokenization.
 * 
 * @param input Input string.
 * @param ctx Tokenizer context.
 * @param msh Pointer to shell structure.
 */
void	handle_quote(char *input, t_tokenizer_ctx *ctx, t_minish *msh);

/**
 * @brief Concatenates a substring to the token accumulator.
 * 
 * @param accum The accumulator string.
 * @param part The part to append.
 * @return New string with appended part.
 */
// char	*append_part(char *accum, char *part);
char	*append_part(char *accum, char *part, t_minish *msh);

/**
 * @brief Resets the quote-tracking state of the tokenizer.
 * 
 * @param ctx Pointer to tokenizer context.
 */
void	reset_quote_state(t_tokenizer_ctx *ctx);

/**
 * @brief Assigns tokenizer context to a token.
 * 
 * @param token Pointer to token to modify.
 * @param ctx Pointer to tokenizer context with state.
 */
void	set_token(t_token *token, t_tokenizer_ctx *ctx);

/**
 * @brief Handles heredoc logic during token parsing and adds it to command.
 * 
 * @param msh Pointer to the shell structure.
 * @param i Pointer to current token index.
 * @param cmd Pointer to the command node being constructed.
 * @return 0 on success, -1 on failure.
 */
int		parce_heredoc(t_minish *msh, int *i, t_cmd *cmd);

/**
 * @brief Extracts a word token from input and adds it to token list.
 * 
 * @param input Full input string.
 * @param i Pointer to current index in input string.
 * @param accum Accumulator for token characters.
 * @param msh Pointer to shell structure.
 * @return 0 on success, -1 on failure.
 */
int		handle_word(char *input, int *i, char **accum, t_minish *msh);

/**
 * @brief Handles single-character redirection tokens (< or >).
 * 
 * @param input Full input string.
 * @param tokens Token array being populated.
 * @param ctx Pointer to tokenizer context.
 * @return 0 on success, -1 on error.
 */
int		handle_single_redirect(char *input,
			t_token *tokens, t_tokenizer_ctx *ctx);

/**
 * @brief Handles double-character redirection tokens (<< or >>).
 * 
 * @param input Full input string.
 * @param tokens Token array being populated.
 * @param ctx Pointer to tokenizer context.
 * @return 0 on success, -1 on error.
 */
int		handle_double_redirect(char *input,
			t_token *tokens, t_tokenizer_ctx *ctx);

#endif