/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:37:48 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/24 17:27:46 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "printf_utils.h"

enum e_input_type
{
	_c = 'c', //character
	_s = 's', //string
	_p = 'p', //pointer
	_d = 'd', //decimal
	_i = 'i', //integer
	_u = 'u', //unsigned integer
	_x = 'x', //hexadecimal (base 16) lowercase format
	_X = 'X', //hexadecimal (base 16) uppercase format
	_percent = '%' // percent
};

enum e_space_type
{
	_bell = '\a',
	_backspace = '\b',
	_tabh = '\t', //horisontal tab
	_endl = '\n',
	_tabv = '\v', //vertical tab
	_formfeed = '\f',
	_carriageret = '\r'
};

int	ft_printf(const char *format, ...);
int	ft_check_space(char space);

#endif
