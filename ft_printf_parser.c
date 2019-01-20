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

/*va_list *ft_get_va_list_item_by_idx(va_list *args_begin, int idx)
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
}*/


int ft_parse_len_specifier(char **frmt, int *w_d_h, int *w_d_l)
{
	if (**frmt == 'h')
	{
		if (!*w_d_h && *(*frmt + 1) == 'h' && *(*frmt)++ && (*w_d_h = 1))
			return (CHAR);
		else
			return (SHORT);
	}
	else if (**frmt == 'l')
	{
		if (!*w_d_l && *(*frmt + 1) == 'l' && *(*frmt)++ && (*w_d_l = 1))
			return (LONG_LONG);
		else
			return (LONG);
	}
	else if (**frmt == 'j' || **frmt == 'z')
		return (SIZE);
	else if (**frmt == 'L')
		return (LD);
	else
		return (NONE);
}

char ft_get_arg_size(char **frmt, int res_int, int res_dbl)
{
	char c;

	c = **frmt;
	if (c)
		(*frmt)++;
	if (c == 'd' || c == 'i' || c == 'u' ||	c == 'x' || c == 'X' || c == 'o'
																|| c == 'b')
	{
		if (res_int >= INT)
			return (res_int == INT ? (char)4 : (char)8);
		return (res_int == CHAR ? (char)1 : (char)2);
	}
	else if ((c == 'c' && res_int == LONG) || c == 'C')
		return (4);
	else if (c == 'c')
		return (1);
	else if (c == 'p' || c == 's' || c == 'S' || c == 'r' || c == 'k')
		return (8);
	else if (c == 'f' || c == 'F' || c == 'e' || c == 'E' || c == 'g'
															|| c == 'G')
		return (res_dbl == DOUBLE ? (char)8 : (char)16);
	else
		return (0);
}

char ft_parse_arg_size(char **frmt)
{
	t_int_lenghts res_int;
	t_dbl_lenghts res_dbl;
	int was_double_h;
	int was_double_l;
	int curr_type;

	res_int = INT;
	res_dbl = DOUBLE;
	was_double_h = 0;
	was_double_l = 0;
	while (**frmt)
	{
		if (**frmt == ' ' || **frmt == '+' || **frmt == '-' || **frmt == '0' ||
			**frmt == '#' || **frmt == '\'' || **frmt == '*')
			(*frmt)++;
		curr_type = ft_parse_len_specifier(frmt, &was_double_h, &was_double_l);
		if (curr_type == NONE)
			return (ft_get_arg_size(frmt, res_int, res_dbl));
		else if (curr_type <= LONG && curr_type > res_int)
			res_int = curr_type;
		else if (curr_type >= DOUBLE && curr_type > res_dbl)
			res_dbl= curr_type;
		(*frmt)++;
	}
	return (0);
}

t_string *ft_get_va_lst_sizes(char *frmt)
{
	t_string *sizes;
	char tmp;

	if (!(sizes = ft_make_string(2)))
		return (0);

	while (*frmt)
	{
		while (*frmt && *frmt++ != '%')
			;
		if (!*frmt || (*frmt == '%' && *frmt++))
			continue;
		while (!ft_isalpha(*frmt))
			frmt++;
		tmp = ft_parse_arg_size(&frmt);
		if (tmp)
			ft_string_push_back(&sizes, tmp);
	}
	return (sizes);
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
