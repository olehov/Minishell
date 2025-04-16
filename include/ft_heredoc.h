/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:20:08 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 13:44:42 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEREDOC_H
# define FT_HEREDOC_H

# include "minishell.h"
# include "ft_minishell_types.h"

# define HEREDOC_FILENAME_PATH "/tmp/heredoc_tmp_"

/**
 * @brief Initializes a heredoc structure with the given delimiter.
 * 
 * @param delimiter The string used to terminate heredoc input.
 * @return Pointer to a newly allocated t_heredoc structure.
 */
t_heredoc	*init_heredoc(char *delimiter);

/**
 * @brief Handles heredoc input until the delimiter is found.
 * Writes input to a temporary file.
 * 
 * @param heredoc Pointer to heredoc structure containing delimiter and filename.
 * @param msh Pointer to the main shell structure.
 * @return 0 on success, -1 on failure.
 */
int			ft_heredoc(t_heredoc *heredoc, t_minish *msh);

/**
 * @brief Checks if the heredoc input line matches the delimiter.
 * 
 * @param delimiter The delimiter string.
 * @return true if line matches the delimiter, false otherwise.
 */
bool		check_delimiter(const char *delimiter);

/**
 * @brief Deletes temporary heredoc files and frees list elements.
 * 
 * @param heredocs Double pointer to the list of heredoc structures.
 */
void		unlink_heredocs(t_list **heredocs);

/**
 * @brief Frees memory allocated for a single heredoc structure.
 * 
 * @param heredoc Pointer to the heredoc structure to be freed.
 */
void		free_heredoc(void *heredoc);

/**
 * @brief Prompts and reads the delimiter line from user input.
 * 
 * @param heredoc Pointer to heredoc structure to store the delimiter.
 * @return 0 on success, -1 on error.
 */
int			get_delimiter(t_heredoc *heredoc);

#endif