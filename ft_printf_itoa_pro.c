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

char		*ft_printf_itoa_pro(unsigned long n, int r, t_arg_data *ad)
{
	static char		bas[] = "0123456789ABCDEF";
	int				l;
	char			*ret;
	unsigned long	nb;
	int 			i;

	/*if (rad == -2)
		return (ft_print_bits(n)); */// TODO
	if (r == 16 || r == -16)
		(r < 0 && (r *= -1)) ? ft_tolower_str(bas) : ft_toupper_str(bas);
	l = 1 + (n != 0) + (ad->sign && r == 10);
	nb = n;
	while (nb >= r && l++)
		nb /= r;
	l += ((l - 2) / 3) * ((i = 1) && ad->spl != 0 && (r == 10 || r == 8));
	l = (ad->prcsn + 1 > l ) ? (ad->prcsn + 1 + (ad->sign && r == 10)) : l;
	if (!(ret = (char *)ft_memalloc(sizeof(char) * l--)))
		return (NULL);
	while ((n || l) && (ret[--l] = bas[(n % r)]))
		if (((n /= r) + 1) && n && !(i++ % 3) && ad->spl && (r == 10 || r == 8))
			ret[--l] = ad->spl;
	ret[0] = (ad->sign && r == 10) ? ad->sign : ret[0];
	return (ret);
}
