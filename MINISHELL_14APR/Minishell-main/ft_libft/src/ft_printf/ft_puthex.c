/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:30:10 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/24 17:30:12 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/printf_utils.h"
#include <stdlib.h>

static int	get_size(unsigned int numb, int divnum)
{
	int	size;

	size = 0;
	if (numb == 0)
	{
		return (1);
	}
	while (numb != 0)
	{
		size++;
		numb /= divnum;
	}
	return (size);
}

int	ft_puthex(unsigned int numb, char *hexbuf)
{
	char			*strnum;
	int				counter;
	int				divnum;
	int				size;

	counter = 0;
	divnum = 16;
	size = get_size(numb, divnum);
	strnum = ft_calloc(sizeof(char), size + 1);
	if (strnum == NULL)
		return (0);
	strnum[size] = '\0';
	if (numb == 0)
	{
		strnum[0] = '0';
	}
	while (numb != 0)
	{
		strnum[--size] = hexbuf[numb % divnum];
		numb /= divnum;
	}
	counter += ft_putstr(strnum, 1);
	free(strnum);
	return (counter);
}
