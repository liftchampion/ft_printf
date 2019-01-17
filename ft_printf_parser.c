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

#include "ft_printf.h"
#include "libft.h"

#include <stdio.h>

va_list *ft_get_va_list_item_by_idx(va_list *args_begin, int idx)
{
	va_list res;
	int i;

	va_copy(res, *args_begin);
	i = 1;
	while (i < idx)
	{
		void *a = va_arg(res, void*);
		printf("%zu\n", res);
		i++;
	}
}


t_int_lenghts ft_is_len_specifier(char **frmt, int *w_d_h, int *w_d_l)
{
	if (**frmt == 'h')
	{
		if (!*w_d_h && *(*frmt + 1) == 'h' && *(*frmt)++ && (*w_d_h = 1))
			return (CHAR);
		else
			return (SHORT);
	}
	else if (**frmt == 'c')
		return (CHAR);
	else if (**frmt == 'l')
	{
		if (!*w_d_l && *(*frmt + 1) == 'l' && *(*frmt)++ && (*w_d_l = 1))
			return (LONG);
		else
			return (LONG_LONG);
	}
	else if (**frmt == 'j' || **frmt == 'z')
		return (SIZE);
	else if (**frmt == 'L')
		return (LD);
	else
		return (NONE);
}

char ft_get_arg_size(char **frmt)
{
	t_int_lenghts res_int;
	t_printf_lenghts res_double;
	int was_double_h;

	res_int = INT;
	was_double_h = 0;
	while (**frmt)
	{
		(*frmt)++;
	}


}

t_string *ft_get_va_lst_sizes(char *frmt)
{
	t_string *sizes;

	if (!(sizes = ft_make_string(2)))
		return (0);

	while (*frmt)
	{
		while (*frmt && *frmt++ != '%')
			;
		if (*frmt == '%' && *frmt++)
			continue;
		while (!ft_isalpha(*frmt))
			frmt++;

		frmt++;
	}
}


void ft_printf_parse_star(char **frmt, va_list *args, va_list *args_begin, int *was_dot)
{

}

t_arg_data ft_printf_parser(char **frmt, va_list *args, char *frmt_begin, va_list *args_begin)
{
	static t_string *va_lst_sizes = 0;
	int tmp;
	t_arg_data *res;
	int was_dot;

	was_dot = 0;
	res = (t_arg_data*)ft_memalloc(sizeof(t_arg_data) * 1);
	while (1)
	{
		if (**frmt == '*')
		{

		}
		if (ft_isdigit(**frmt))
			tmp = ft_atoi_m(frmt);
		break; // TODO remove
		//if (**frmt == '$')
		//	res->
	}
}
