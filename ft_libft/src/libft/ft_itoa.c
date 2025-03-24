/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:13:03 by ogrativ           #+#    #+#             */
/*   Updated: 2024/04/14 16:13:05 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../headers/libft.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>

static int	ft_ismin(int *nb)
{
	if (*nb == -2147483648)
	{
		*nb += 1;
		return (1);
	}
	return (0);
}

static int	ft_size(int n, int sign)
{
	int	size;

	size = 0;
	if (n == 0)
	{
		return (1);
	}
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	if (sign == -1)
	{
		return (size + 1);
	}
	return (size);
}

static int	ft_sign(int n)
{
	if (n >= 0)
	{
		return (1);
	}
	else
	{
		return (-1);
	}
}

static char	*ft_min(char *s, int size, int sign, int ismin)
{
	if (sign == -1)
	{
		if (ismin == 1)
		{
			s[size - 1] += 1;
		}
		s[0] = '-';
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		sign;
	int		size;
	int		size2;
	int		ismin;

	sign = ft_sign(n);
	ismin = ft_ismin(&n);
	size = ft_size(n, sign);
	n *= sign;
	size2 = size;
	number = (char *)malloc(sizeof(char) * (size + 1));
	if (number == NULL)
		return (NULL);
	if (n == 0)
		number[0] = n + '0';
	while (n != 0)
	{
		number[--size] = (n % 10) + '0';
		n /= 10;
	}
	number[size2] = '\0';
	number = ft_min(number, size2, sign, ismin);
	return (number);
}

// void test_case(int n, const char *expected) {
//     char *result = ft_itoa(n);
//     if (result == NULL) {
//         printf("Test failed: Memory allocation failed for input %d\n", n);
//         return;
//     }
//     if (strcmp(result, expected) == 0) {
//         printf("Test passed: %d -> %s\n", n, result);
//     } else {
//         printf("Test failed: %d -> %s (exp: %s)\n", n, result, expected);
//     }
//     free(result); // Free memory allocated by ft_itoa
// }

// int main() {
//     // Positive Numbers
//     test_case(123, "123");
//     test_case(0, "0");
//     test_case(INT_MAX, "2147483647");

//     // Negative Numbers
//     test_case(-456, "-456");
//     test_case(INT_MIN, "-2147483648");

//     // Zero
//     test_case(0, "0");

//     // Edge Cases
//     test_case(INT_MAX, "2147483647");
//     test_case(INT_MIN, "-2147483648");
//     test_case(INT_MIN + 1, "-2147483647");
//     test_case(INT_MAX - 1, "2147483646");

//     // Random Numbers
//     test_case(987654321, "987654321");
//     test_case(-987654321, "-987654321");

//     return 0;
// }