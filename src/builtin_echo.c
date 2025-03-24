/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:43:08 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/15 15:47:01 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Функція для echo з підтримкою -n
void ft_echo(char **args)
{
    int i = 0;
    int newline = 1;

    // Перевірка на опцію -n (може бути декілька -n: echo -n -n hello)
    while (args[i] && ft_strncmp(args[i], "-n", 2) == 0 && only_n(args[i]))
    {
        newline = 0;
        i++;
    }

    // Виведення аргументів
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }

    // Додаємо новий рядок, якщо не було -n
    if (newline)
        printf("\n");
}

// // Перевіряє, чи рядок складається тільки з -n
// int only_n(char *str)
// {
//     int i = 1; // Починаємо з другого символу, бо перший '-'
//     if (str[0] != '-')
//         return 0;
//     while (str[i])
//     {
//         if (str[i] != 'n')
//             return 0;
//         i++;
//     }
//     return 1;
// }
