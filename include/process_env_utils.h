/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:41:57 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/10 15:08:04 by ogrativ          ###   ########.fr       */
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

typedef struct s_env_state
{
	char	*result;
	int		res_index;
	size_t	result_size;
	char	quote;
	t_list	*lst;
}	t_env_state;

int	process_quoted_text(const char *input, int start, t_env_state *state);

int	extract_quoted_text(const char *input, int *i, t_env_state *state);

/**
 * @brief Extracts the name of a variable starting from
 * a specific position in the input string.
 * Supports both $VAR and ${VAR} formats.
 * @param input: The input string containing the variable.
 * @param start: The starting position of the variable name.
 * @param var_name: Buffer to store the extracted variable name.
 * @param max_len: The maximum length of the variable name.
 * @return The updated position in the input string after the variable name.
*/
// int		extract_variable_name(const char *input, int start,
// 			char *var_name, int max_len);

int	extract_variable_value(const char *input, int	*i, t_env_state *state);
int	extract_variable(const char *input, int *i, t_env_state *state);

/**
 * @brief Check if enough capacity for add text
 * if not rellocate memory with current line (length * 2 + extra_len).
 * @param state: The state structure containing the result buffer and index.
 * @param extra_length: len of adding line
 * @return Return 0 if success and -1 if can't allocate memory
 */
int	ensure_buffer_capacity(t_env_state *state, int extra_length);
int	try_ensure_buffer_capacity(t_env_state *state,
		int extra_length, char c);
/**
 * @brief Handles escaping for special characters (e.g., \\$, \${}).
 * Ensures that escaped characters are treated literally in the result buffer.
 * @param input: The input string.
 * @param i: Pointer to the current position in the input string.
 * @param state: The state structure containing the result buffer and index.
 * @return 1 if the escaping was handled, 0 otherwise.
*/
int	handle_escaping_variable(const char *input, int *i, t_env_state *state);

/**
 * @brief Appends the value of an environment variable to the result buffer.
 * @param var_name: The name of the environment variable.
 * @param state: The state structure containing the result buffer and index.
 * @param lst: The list of environment variables (t_list).
*/
int	append_variable_value(const char *var_name,
		t_env_state *state, t_list *lst);

#endif