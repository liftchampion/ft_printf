/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:36:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/23 17:18:07 by ehugh-be         ###   ########.fr       */
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
	printf("overflow_arg_area - %ld reg_save_area - %ld\n", (*(t1)) , *(t2 + 3));
}

void ft_print_items_vector(void **vec)
{
	t_res_item	*res_item;

	printf("args:<");
	while (*vec)
	{
		res_item = *(t_res_item**)vec;
		if (res_item->item_type == I_STRING)
		{
			for (int g = 0; g < res_item->str_len; g++)
			{
				printf("%c", ((char*)res_item->item_ptr)[g]);
			}
		}
		else if (res_item->item_type == I_VAR)
		{
			printf("[%d]", ((t_arg_data*)res_item->item_ptr)->num);
		}
		vec++;
	}
	printf(">\n");
}

int	ft_printf(const char *frmt, ...)
{
	va_list		vl;
	t_string	*str;
	t_string	*args_seq;
	t_res_item	*res_item;

	va_start(vl, frmt);

	void	**res_items;  // TODO use vector
	int counter = 0;  // TODO delete when will use vector
	res_items = (void**)ft_memalloc(sizeof(void*) * 100); // TODO use vector


	t_arg_data *arg_data = 0;


	if (!(str = ft_make_string(1)))
		return (0);
	if (!(args_seq = ft_make_string(1)))
	{
		ft_free_string(&str);
		return (0);
	}

	while (*frmt)
	{
		if (!(res_item = ft_find_cntrl(&frmt)))
			return (-1);
		res_items[counter++] = (void*)res_item; // TODO use vector
		if (*(frmt - 1) == '{') // TODO dangerous -1
			ft_set_color(&frmt, &str);
		else if (*frmt)
		{
			if (!(res_item = ft_printf_parser((char**) &frmt, &args_seq)))
				return (-1);
			res_items[counter++] = (void*)res_item;	// TODO use vector
		}

		//ft_stringify(&str, arg_data, args_seq);
	}
	ft_print_items_vector(res_items);
	ft_print_string(args_seq); // TODO delete it
	printf("\n");
	///ft_print_string(str);
	ft_free_string(&str);
	ft_free_string(&args_seq);
	printf("\n");

	va_end(vl);
	return (0);
}
