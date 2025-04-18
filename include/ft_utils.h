/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:02:27 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 06:24:33 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "ft_minishell_types.h"

bool	is_only_digit(char *str);
bool	ft_is_directory(const char *path);

size_t	get_row_size(char **args);

int		ft_decode_wstatus(int wstatus);
int		ft_syntax_error(char *input);

char	*get_prompt(t_minish *msh);
char	*remove_quotes(char *str);
char	**split_path(t_list *lst, char *key, char c);
char	**split_outside_quotes(char *input, char delimiter);

void	print_syntax_err(char *str);

void	free_tokens(t_token *tokens);

#endif