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
#include <stdio.h>

void ft_print_va_struct(va_list ls)
{
	printf("gp_offs - %u fp_offs - %u overflow_arg_area - %p reg_save_area - %p\n",
			ls->gp_offset, ls->fp_offset, ls->overflow_arg_area, ls->reg_save_area);
	long int *t1 = (long int *)ls->overflow_arg_area;
	long int *t2 = (long int *)ls->reg_save_area;
	printf("overflow_arg_area - %ld reg_save_area - %ld\n",
			(*(t1)) , *(t2 + 3));
}


int	ft_printf(const char *frmt, ...)
{
	va_list		vl;
	t_string	*str;


	va_start(vl, frmt);


	str = ft_make_string(1);
	while (*frmt)
	{
		while (*frmt && *frmt != '%')
			frmt++;
		if (!*frmt)
			break;
		frmt++;
		ft_printf_parser((char**)&frmt, str);
		//ft_stringify(&str, vl);
	}
	printf("\n");
	ft_print_string(str);
	ft_free_string(&str);
	printf("\n");

	ft_printf_parser(0, 0);
	va_end(vl);
	return (0);
}
