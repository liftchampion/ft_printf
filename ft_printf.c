/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:36:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/17 18:13:10 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf(const char *frmt, ...)
{
	va_list		vl;
	t_string	*str;

	va_start(vl, frmt);
	str = ft_make_string(1);
	while (*frmt)
	{
		ft_find_cntrl(&frmt, &str);
		ft_printf_parser(&frmt, &vl, vl);
		ft_stringify(&str, vl);
	}
	va_end(vl);
	return (0);
}
