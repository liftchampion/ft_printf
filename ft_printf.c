/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:36:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/27 02:27:36 by ehugh-be         ###   ########.fr       */
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
	printf("overflow_arg_area - %ld reg_save_area - %ld   delta = %zu\n",
			(*(t1)) , *(t2 + 3), ls->overflow_arg_area - ls->reg_save_area);
}

int	ft_printf(const char *frmt, ...)
{
	va_list		vl;
	t_string	*str[100];
	int			i;
	t_string	*args_seq;
	t_arg_data	*vars[99];


	va_start(vl, frmt);
	ft_print_va_struct(vl);
	for (int e = 0; e < 28; e++)
	{
		if (e < 8)
		{
			if (e != 4)
			{
				int x = va_arg(vl, int);
				printf("%d $\n", x);
				ft_print_va_struct(vl);
			}
			else
			{
				__int128_t x = 0;
				unsigned long x1 = 0;
				unsigned long x2 = 0;

				//x = va_arg(vl, __int128_t);
				x1 = va_arg(vl, unsigned long);
				x2 = va_arg(vl, unsigned long);
				printf("%ld  %ld %ld ###\n", (long)x, x1, x2);
				ft_print_va_struct(vl);
			}
		}
		else if (e != 20)
		{
			double x = va_arg(vl, double);
			printf("%f\n", x);
			ft_print_va_struct(vl);
		}
		else
		{
			//vl->overflow_arg_area -= 8;
			__int128_t x = 0;
			unsigned long x1 = 0;
			unsigned long x2 = 0;

			x = *(__int128_t*)vl->overflow_arg_area;
			vl->overflow_arg_area += 16;

			//x = va_arg(vl, __int128_t);
			//x1 = va_arg(vl, unsigned long);
			//x2 = va_arg(vl, unsigned long);
			//x = (x << 64);
			//x = (x >> 64);
			unsigned long lu = x;
			printf("%lu   !!! %lu %lu\n", lu, x1, x2);
			ft_print_va_struct(vl);
		}
	}
	/*va_arg(vl, float);
	ft_print_va_struct(vl);
	va_arg(vl, double);
	ft_print_va_struct(vl);
	va_arg(vl, long double);
	ft_print_va_struct(vl);
	va_arg(vl, double);
	ft_print_va_struct(vl);*/

	args_seq = ft_make_string(1);
	i = 0;
	str[i] = ft_make_string(1);
	while (*frmt)
	{
		if (!ft_find_cntrl(&frmt, &str[i]))
			return (-1);
		if (*(frmt - 1) == '{')
		{
			if (ft_set_color(&frmt, &str[i]))
				return (-1);
		}
		else
		{
			vars[i++] = ft_printf_parser(&frmt, &args_seq);
			str[i] = ft_make_string(1);
		}
	}
	//ft_stringify(&str[0], vars, vl, args_seq);
	//ft_print_string_arr(str, i);
	//ft_free_string_arr(str, i);

	va_end(vl);
	return (0);
}
