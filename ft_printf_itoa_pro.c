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

char		*ft_printf_itoa_pro(__int128_t n, int rad)
{
	static char		base[] = "0123456789ABCDEF";
	__int128_t		nb;
	int				len;
	char			*ret;

	int prec = 0;

	len = 2 + (n < 0);
	nb = n;
	while (!(nb < rad && nb > -rad))
	{
		len++;
		nb /= rad;
	}
	len = prec > len ? prec : len;
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ret[--len] = '\0';
	nb = (n < 0) ? -1 : 1;
	while (n || len)
	{
		ret[--len] = base[n % rad * nb];
		n /= rad;
	}
	if (nb < 0)
		ret[0] = '-';
	return (ret);
}