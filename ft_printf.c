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

typedef union un2
{
	long double db;
	long int ints[2];
}			t_un2;

#define VA_ARG(vl, typ) va_arg(vl, typ)

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
	va_list vl;

	int x;

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

	/**char *frmt_begin = frmt;
	va_list start;
	va_copy(start, vl);
	while (*frmt)
	{
		while (*frmt && *frmt != '%')
			frmt++;
		if (*frmt)
		{
			frmt++;
			ft_printf_parser((char**) &frmt, &vl, frmt_begin, &start);
		}

	}*/

	printf("va_list is:\n");

	/*for (int e = 0; e < 7; e++)
	{
		//va_list tmp;
		//ft_get_va_list_item_by_idx(&vl, e, &tmp, (char*)frmt);
		if (e == 1)
		{
			long double t = va_arg(vl, long double);
			printf("%Lf\n", t);
			continue;
		}
		long int a = va_arg(vl, long int);
		printf("%d\n", a);
	}
	*/

	/*__builtin_va_start(44, 66);
	__builtin_va_list tt;
	tt->reg_save_area;
	struct __va_list_tag *hh;*/

	printf("mem is:\n");
	printf("%s \n", ft_itoa_base((size_t)&frmt, 16));

	ft_print_va_struct(vl);
	long g = va_arg(vl, long);
	//int g;
	ft_print_va_struct(vl);
	//double h = va_arg(vl, double);
	//ft_print_va_struct(vl);
	g = va_arg(vl, long);
	ft_print_va_struct(vl);
	g = va_arg(vl, long);
	ft_print_va_struct(vl);
	g = va_arg(vl, long);
	ft_print_va_struct(vl);
	g = va_arg(vl, long);
	ft_print_va_struct(vl);
	g = va_arg(vl, long);
	ft_print_va_struct(vl);
	g = va_arg(vl, long);
	ft_print_va_struct(vl);
	int ii = va_arg(vl, int);
	ft_print_va_struct(vl);
	char cc = va_arg(vl, char);
	ft_print_va_struct(vl);
	short int ss = va_arg(vl, short int);
	ft_print_va_struct(vl);
	printf("start for\n");
	for (int t = 1; t <= 23; t++)
	{
		if (t == 19 || t == 21)
		{
			printf("INT\n");
			__int128_t y = va_arg(vl, __int128_t);
			ft_print_va_struct(vl);
			continue;
		}
		long double y = va_arg(vl, long double);
		ft_print_va_struct(vl);
	}

	/*unsigned char *start = (unsigned char *)vl;
	//start += 16;

	printf("%d \n", *start);
	long g = va_arg(vl, long);
	//__int128_t g = va_arg(vl, __int128_t);
	long int g2 = va_arg(vl, long int);
	unsigned char *start2 = (unsigned char *)vl;
	printf("%d === %zu\n",(int)g, *start2 - *start);
	///for (int j = 0; j < 8; j++)
	///	printf("%X -- \n", *(start + j));
	//start += 8;
	printf("%p %p\n", start, start2);
	for (int e = 0; e < 8; e++)
	{
		printf("%p ", *start);
		if ((e + 1) % 4 == 0)
			printf(" ");
		//printf("%d ", *start);
		start++;
	}*/

	//ft_get_va_list_item_by_idx(vl, 2);


	va_end(vl);
	return (0);
}
