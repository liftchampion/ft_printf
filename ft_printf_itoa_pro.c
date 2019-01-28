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
#include "printf.h"

#include <stdio.h> // TODO delete it



char		*ft_printf_itoa_pro(__int128_t n, int rad, int prec, char sign)
{
	static char		base[] = "0123456789ABCDEF";
	int				len;
	char			*ret;
	__int128_t		nb;

	len = 2 + ((sign && rad == 10) || n < 0);
	nb = n;
	while (!(nb < rad && nb > -rad))
	{
		len++;
		nb /= rad;
	}
	nb = n < 0 ? -1 : 1;
	len = (prec > len ) ? (prec + 1 + (n < 0 || (sign && rad == 10))) : len;
	printf("len = %d\n", len);
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ret[--len] = '\0';
	while (n || len)
	{
		ret[--len] = base[(n % rad) * nb];
		///printf("%c<%lld> ", base[(n % rad) * nb], (n % rad) * nb);
		n /= rad;
	}
	///printf("\n");
	if ((sign && rad == 10) || nb < 0)
		ret[0] = nb < 0 ? (char)'-' : sign;
	return (ret);
}