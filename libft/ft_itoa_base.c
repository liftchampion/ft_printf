/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2018/11/29 16:09:36 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_itoa_base(int n, int radix)
{
	static char	base[] = "0123456789ABCDEF";
	int			nb;
	int			len;
	char		*ret;

	len = 2 + (n < 0);
	nb = n;
	while (!(nb < radix && nb > -radix))
	{
		len++;
		nb /= radix;
	}
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ret[--len] = '\0';
	nb = (n < 0) ? -1 : 1;
	while (n || len)
	{
		ret[--len] = base[n % radix * nb];
		n /= radix;
	}
	if (nb < 0)
		ret[0] = '-';
	return (ret);
}
