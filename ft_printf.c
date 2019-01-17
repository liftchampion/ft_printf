/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:36:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/16 23:43:56 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

#define VA_ARG(vl, typ) va_arg(vl, typ)

int	ft_printf(const char *frmt, ...)
{
	va_list vl;

	va_start(vl, frmt);

	/*for (int e = 0; e < 10; e++)
	{
		int i = 1;
		while (i < e)
		{
			va_list res;
			va_copy(res, vl);
			int a = va_arg(res, int);
			printf("%d\n", a);
			i++;
			va_end(res);
		}
	}*/

	for (int e = 0; e < 10; e++)
	{
		int a = va_arg(vl, int);
		printf("%d\n", a);
	}

	//ft_get_va_list_item_by_idx(vl, 2);


	va_end(vl);
	return (0);
}
