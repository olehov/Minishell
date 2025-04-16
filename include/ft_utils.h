/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:02:27 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:03:14 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "ft_minishell_types.h"

bool	is_only_digit(char *str);
char	*get_prompt(t_minish *msh);
size_t	get_row_size(char **args);
bool	ft_is_directory(const char *path);
int		ft_decode_wstatus(int wstatus);
char	*remove_quotes(char *str);
char	**split_path(t_list *lst, char *key, char c);
void	free_tokens(t_token *tokens);
char	**split_outside_quotes(char *input, char delimiter);

#endif