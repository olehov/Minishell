/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:42:37 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/15 14:42:54 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// // ======= CD =======
// void ft_cd(char *path, t_list **lst)
// {
//     t_env *env;
//     char buf[PATH_MAX];
//     char old_path[PATH_MAX];

//     if (getcwd(old_path, PATH_MAX) == NULL)
//         return;

//     if (!path)
//     {
//         env = ft_get_env(*lst, "HOME");
//         if (!env || chdir(env->value) != 0)
//             return (perror("cd"));
//     }
//     else if (ft_strcmp(path, "-") == 0)
//     {
//         env = ft_get_env(*lst, "OLDPWD");
//         if (!env || chdir(env->value) != 0)
//             return (perror("cd"));
//         printf("%s\n", env->value);
//     }
//     else if (chdir(path) != 0)
//         return (perror("cd"));

//     // Оновлюємо OLDPWD і PWD
//     env = ft_get_env(*lst, "OLDPWD");
//     if (env) { free(env->value); env->value = ft_strdup(old_path); }
//     env = ft_get_env(*lst, "PWD");
//     if (env) { free(env->value); getcwd(buf, PATH_MAX); env->value = ft_strdup(buf); }
// }

// // ======= PWD =======
// void printpwd(void)
// {
//     char buf[PATH_MAX];
//     if (getcwd(buf, PATH_MAX) == NULL)
//         perror("pwd");
//     else
//         printf("%s\n", buf);
// }

// // ======= ENV =======
// void print_env_list(t_list *lst)
// {
//     t_env *env;
//     while (lst)
//     {
//         env = (t_env *)lst->content;
//         if (env->value)
//             printf("%s=%s\n", env->key, env->value);
//         lst = lst->next;
//     }
// }

// // ======= EXPORT =======
// int ft_set_env(t_list **lst, char *env)
// {
//     t_env *var;
//     char **tmp;
//     size_t i = 0;

//     if (!env) return (-1);
//     tmp = ft_split(env, ' ');
//     if (!tmp) return (-1);
//     while (tmp[i])
//     {
//         var = parce_env(tmp[i++]);
//         if (!var) continue;
//         t_list *node = ft_get_env_node(*lst, var->key);
//         if (node)
//         {
//             free_env(node->content);
//             node->content = var;
//         }
//         else
//             ft_lstadd_back(lst, ft_lstnew(var));
//     }
//     return (ft_free_2d_array(tmp, i), 0);
// }

// // ======= UNSET =======
// void ft_env_unset(t_list **lst, char *env)
// {
//     t_list *node = ft_get_env_node(*lst, env);
//     t_list *prev = NULL;
//     t_list *curr = *lst;
//     if (!node) return;

//     while (curr && curr != node)
//     {
//         prev = curr;
//         curr = curr->next;
//     }

//     if (prev)
//         prev->next = curr->next;
//     else
//         *lst = curr->next;

//     ft_lstdelone(curr, free_env);
// }

// ======= EXIT =======
void ft_exit(char **args)
{
    int status = 0;
    if (args[0])
        status = ft_atoi(args[0]);
    printf("exit\n");
    exit(status);
}
