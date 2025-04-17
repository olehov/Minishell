/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfedorys <mfedorys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:04 by mfedorys          #+#    #+#             */
/*   Updated: 2025/04/17 17:11:37 by mfedorys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"
#include "../../include/ft_cmd.h"
#include <fcntl.h>
#include <unistd.h>


//TODO NORM!!!
static int  checking_rest(char *input, int flag)
{
    int i;

    i = 0;
    while(input[++i])
    {
        if(flag == 1 && (input[i] == '|' || input[i] == '<' || input[i] == '>'))
            return (1);
        else if(flag == 1 && ft_isalnum(input[i]) && !ft_isspace(input[i]) && input[i] != '\0')
            flag = 0;
        if(input[i] == '|' || (input[i] == '<' && input[i+1] != '<') || (input[i] == '>' && input[i+1] != '>'))  // checking only 1 charackter
            flag = 1;
        else if ((input[i] == '<' && input[i+1] == '<') || (input[i] == '>' && input[i+1] == '>')) // checking both chars
        {
            flag = 1;
            i++;
        }
    }
    return (flag);
}


int ft_syntax_error(char *input)
{
    int i;
    int flag;

    i = -1;
    if(input[++i] == '|')
        return (1);
    while(ft_isspace(input[++i]))
    {
        if(input[i+1] == '|')
            return (1);
    }
    flag = 0;
    flag = checking_rest(input, flag);
    return (flag);
}
