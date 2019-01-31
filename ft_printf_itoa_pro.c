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


unsigned long ft_printf_int_caster(void* n, t_arg_sz size, char us, char *sign)
{
	if (size == CHAR && (us || ((*(char*)n < 0 && (*sign = '-'))) ||
															(*(char*)n >= 0)))
		return (us ? *(unsigned char*)n :
					(unsigned char)(*(char*)n * ((*sign == '-') ? -1 : 1)));
	else if (size == SHORT && (us || ((*(short*)n < 0 && (*sign = '-'))) ||
															(*(short*)n >= 0)))
		return (us ? *(unsigned short*)n :
					(unsigned short)(*(short*)n * ((*sign == '-') ? -1 : 1)));
	else if (size == DEFAULT && (us || ((*(int*)n < 0 && (*sign = '-'))) ||
															(*(int*)n >= 0)))
		return (us ? *(unsigned int*)n :
					(unsigned int)(*(int*)n * ((*sign == '-') ? -1 : 1)));
	else if (size == LONG && (us || ((*(long*)n < 0 && (*sign = '-'))) ||
															(*(long*)n >= 0)))
		return (us ? *(unsigned long*)n :
					(unsigned long)(*(long*)n * ((*sign == '-') ? -1 : 1)));
	else
		return (*(unsigned long*)n);
}

char		*ft_printf_itoa_pro(unsigned long n, int rad, t_arg_data *arg_data)
{
	static char		bas[] = "0123456789ABCDEF";
	int				len;
	char			*ret;
	unsigned long	nb;
	int 			i;

	/*if (rad == -2)
		return (ft_print_bits(n)); */// TODO
	if (rad == 16 || rad == -16)
		(rad < 0 && (rad *= -1)) ? ft_tolower_str(bas) : ft_toupper_str(bas);
	len = 1 + (n != 0) + (arg_data->sign && rad == 10);
	nb = n;
	while (nb >= rad && len++)
		nb /= rad;
	len += ((len - 1) / 3) * ((i = 1) && arg_data->apostrophe != 0 && (rad == 10 || rad == 8));
	len = (arg_data->prcsn + 1 > len ) ? (arg_data->prcsn + 1 +
										(arg_data->sign && rad == 10)) : len;
	if (!(ret = (char *)ft_memalloc(sizeof(char) * len--)))
		return (NULL);
	while ((n || len) && (ret[--len] = bas[(n % rad)]))
	{
		n /= rad;
		if (arg_data->apostrophe && !(i % 3) && n && (rad == 10 || rad == 8))
			ret[--len] = arg_data->apostrophe;
		i++;
	}
	ret[0] = (arg_data->sign && rad == 10) ? arg_data->sign : ret[0];
	return (ret);
}
