/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 03:00:46 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/27 04:24:46 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

#include <stdio.h> // TODO delete it

int ft_print_bits(unsigned long n)
{
	for (int e = sizeof(n) * 8 - 1; e >= 0; e--)
	{
		printf("%d", (n & (1L << e)) != 0);
		if (e % 8 == 0)
			printf(" ");
	}
	printf("\n");
	return (1);
}


__int128_t ft_printf_int_caster(__int128_t n, t_arg_sz size, char us)
{
	if (size == CHAR)
		return (us ? (unsigned char)n : (char)n);
	else if (size == SHORT)
		return (us ? (unsigned short)n : (short)n);
	else if (size == DEFAULT)
		return (us ? (unsigned int)n : (int)n);
	else if (size == LONG)
		return (us ? (unsigned long)n : n);
	else
		return (n);
}

char		*ft_printf_itoa_pro(__int128_t n, int rad, int prec, char sign)
{
	static char		bas[] = "0123456789ABCDEF";
	int				len;
	char			*ret;
	__int128_t		nb;

	if (rad == -2)
		return (ft_print_bits(n)); // TODO
	if (rad == 16 || rad == -16)
		(rad < 0 && (rad *= -1)) ? ft_tolower_str(bas) : ft_toupper_str(bas);
	len = 1 + (n != 0) + ((sign && rad == 10) || n < 0);
	nb = n;
	while (!(nb < rad && nb > -rad) && len++)
		nb /= rad;
	nb = n < 0 ? -1 : 1;
	len = (prec > len ) ? (prec + 1 + (n < 0 || (sign && rad == 10))) : len;
	if (!(ret = (char *)ft_memalloc(sizeof(char) * len--)))
		return (NULL);
	while ((n || len) && (ret[--len] = bas[(n % rad) * nb]))
		n /= rad;
	if ((sign && rad == 10) || nb < 0)
		ret[0] = nb < 0 ? (char)'-' : sign;
	return (ret);
}