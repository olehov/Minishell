/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:06:15 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:37:17 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "ft_minishell_types.h"
# include "ft_utils.h"
# include "process_env_utils.h"

int		init_env(t_list **lst, char *env[]);

int		ft_set_env(t_list **lst, char *env);

t_env	*ft_get_env(t_list *lst, char *key);
t_list	*ft_get_env_node(t_list *lst, char *key);
char	*get_env_value(const char *var_name, t_list *lst);
void	print_env_list(t_list *lst);

char	**env_list_to_str_arr(t_list *lst);
// char	*expand_dbl_quote(char *line, int *i, t_minish *msh);
char	*process_env(const char *input, t_list *lst, t_minish *msh);
t_env	*parce_env(char *env);

void	ft_env_unset(t_list **lst, char *env);
void	free_env(void *env);

#endif