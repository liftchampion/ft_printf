/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:36:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/18 14:39:38 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *frmt, ...)
{
	va_list		vl;
	t_string	*str;

	va_start(vl, frmt);
	str = ft_make_string(1);
	while (*frmt)
	{
		if (!ft_find_cntrl(&frmt, &str))
			return (1);
		//ft_printf_parser(&frmt, &vl, vl);
		//ft_stringify(&str, vl);
	}
	ft_print_string(str);
	ft_free_string(&str);
	va_end(vl);
	return (0);
}
