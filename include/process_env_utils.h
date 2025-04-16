/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:41:57 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 11:25:28 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_ENV_UTILS_H
# define PROCESS_ENV_UTILS_H

# include "../include/minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>

/**
 * @brief Structure used to maintain state during environment variable parsing.
 */
typedef struct s_env_state
{
	char	*result;		///< Buffer holding the resulting processed string.
	int		res_index;		///< Current index in the result buffer.
	size_t	result_size;	///< Current size of the allocated buffer.
	char	quote;			///< Current quote context (single/double).
	t_list	*lst;			///< Pointer to environment variable list.
}	t_env_state;

/**
 * @brief Processes a quoted substring from the input and adds it to result.
 * 
 * @param input The full input string.
 * @param start The starting index of the quoted text.
 * @param state Pointer to the environment parsing state.
 * @param msh Pointer to main shell structure.
 * @return New index in the input after processing, or -1 on error.
 */
int	process_quoted_text(const char *input, int start,
		t_env_state *state, t_minish *msh);

/**
 * @brief Extracts a quoted section from the input string.
 * 
 * @param input The input string containing quotes.
 * @param i Pointer to the current index in input string.
 * @param state Pointer to environment parsing state.
 * @param msh Pointer to the shell structure.
 * @return 0 on success, non-zero on error.
 */
int	extract_quoted_text(const char *input, int *i,
		t_env_state *state, t_minish *msh);

/**
 * @brief Extracts the value of a variable starting from the given position.
 * Supports $VAR and ${VAR} syntax.
 * 
 * @param input Input string containing the variable.
 * @param i Pointer to the current index in the input string.
 * @param state Pointer to environment parsing state.
 * @param msh Pointer to main shell structure.
 * @return 0 on success, non-zero on failure.
 */
int	extract_variable_value(const char *input, int *i,
		t_env_state *state, t_minish *msh);

/**
 * @brief Extracts both the name and value of a variable, and appends its value.
 * 
 * @param input The input string.
 * @param i Pointer to the current index.
 * @param state Pointer to the parsing state.
 * @param msh Pointer to the shell state.
 * @return 0 on success, -1 on error.
 */
int	extract_variable(const char *input, int *i,
		t_env_state *state, t_minish *msh);

/**
 * @brief Ensures there is enough buffer capacity to add new text.
 * Resizes the buffer if needed.
 * 
 * @param state Pointer to environment parsing state.
 * @param extra_length Number of characters to be added.
 * @return 0 on success, -1 on failure to reallocate.
 */
int	ensure_buffer_capacity(t_env_state *state, int extra_length);

/**
 * @brief Same as ensure_buffer_capacity, but considers adding a single char.
 * 
 * @param state Pointer to environment parsing state.
 * @param extra_length Estimated length of new content.
 * @param c Character that might be appended.
 * @return 0 on success, -1 on failure.
 */
int	try_ensure_buffer_capacity(t_env_state *state,
		int extra_length, char c);

/**
 * @brief Handles escaping of variables like \$VAR and \${VAR}.
 * Ensures escaped variables are treated literally.
 * 
 * @param input The full input string.
 * @param i Pointer to current index in the string.
 * @param state Pointer to the environment parsing state.
 * @return 1 if escaping was handled, 0 otherwise.
 */
int	handle_escaping_variable(const char *input, int *i, t_env_state *state);

/**
 * @brief Appends the value of a given variable to the result buffer.
 * 
 * @param var_name The name of the environment variable.
 * @param state Pointer to result buffer and parsing state.
 * @param lst List of environment variables.
 * @return 0 on success, -1 if variable not found or memory error.
 */
int	append_variable_value(const char *var_name,
		t_env_state *state, t_list *lst);

#endif