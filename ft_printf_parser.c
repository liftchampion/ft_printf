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

int ft_get_va_list_item_by_idx(va_list args_begin, int idx, va_list *res,
											char *frmt_begin)
{
	static t_string *sizes = 0;
	int i;

	i = 0;
	if (args_begin == 0 && idx == 0 && res == 0)   /// 'close' sizes vector after end of printf
		ft_free_string(&sizes);
	if (sizes == 0 && idx != 0)
		if (!(sizes = ft_get_va_lst_sizes(frmt_begin)))
		{
			ft_free_string(&sizes);
			return (0);
		}
	va_copy(*res, args_begin);
	while (i < idx)
	{
		if (sizes->data[i] <= 4)
			va_arg(*res, int);
		else if (sizes->data[i] == 8)
			va_arg(*res, long int);
		else if (sizes->data[i] == 16)
			va_arg(*res, __int128_t); // TODO think about long double / __int128_t
		i++;
	}
	return (1);
}


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
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == 'o'
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

t_cntrl_cases ft_parse_arg_size_check_one_cntrl_block(char **frmt, t_string **sizes)
{
	int was_star;
	int was_num;
	int was_dollar;

	was_star = 0;
	was_num = 0;
	was_dollar = 0;
	if ((**frmt == ' ' || **frmt == '+' || **frmt == '-' || **frmt == '0' ||
								**frmt == '#' || **frmt == '\'') && (*frmt)++)
		return (NEUTRAL);
	if (**frmt == '*' && (*frmt)++)
		was_star = 1;
	while (**frmt && ft_isdigit(**frmt) && (*frmt)++)
		was_num = 1;
	if (**frmt == '$' && (*frmt)++)
		was_dollar = 1;
	if (was_star && !was_dollar)
	{
		ft_string_push_back(sizes, 4);
		return (ADD_VA_LST_ITEM);
	}
	if (was_num && was_dollar && !was_star)
		return (DONT_ADD_VA_LST_ITEM);
	return (was_star + was_num + was_dollar == 0 ? NO_CNTL : NEUTRAL);
}

t_cntrl_cases ft_parse_arg_size_check_cntrl(char **frmt, t_string **sizes)
{
	int dont_add_va_ls_item;
	t_cntrl_cases curr_case;

	dont_add_va_ls_item = 0;
	while ((curr_case = ft_parse_arg_size_check_one_cntrl_block(frmt, sizes)))
	{
		if (curr_case == DONT_ADD_VA_LST_ITEM)
			dont_add_va_ls_item = 1;
	}
	return (dont_add_va_ls_item ? DONT_ADD_VA_LST_ITEM : NEUTRAL);
}

char ft_parse_arg_size(char **frmt, t_string **sizes)
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
		if (ft_parse_arg_size_check_cntrl(frmt, sizes) == DONT_ADD_VA_LST_ITEM)
			return (0);
		curr_type = ft_parse_len_specifier(frmt, &was_double_h, &was_double_l);
		if (curr_type == NONE)
			return (ft_get_arg_size(frmt, res_int, res_dbl));
		else if (curr_type <= LONG && (t_int_lenghts)curr_type > res_int)
			res_int = curr_type;
		else if (curr_type >= DOUBLE && (t_dbl_lenghts)curr_type > res_dbl)
			res_dbl = curr_type;
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
		while (!ft_isalpha(*frmt) && *frmt != '*' && *frmt != '$'
													&& !ft_isdigit(*frmt))
			frmt++;
		tmp = ft_parse_arg_size(&frmt, &sizes);
		if (tmp == -1)
			return (0);
		if (tmp)
			if (!ft_string_push_back(&sizes, tmp))
				return (0);
	}
	return (sizes);
}


/*void ft_printf_parse_star(char **frmt, va_list *args, va_list *args_begin, int *was_dot)
{

}*/

/*t_arg_data ft_printf_parser(char **frmt, va_list *args, char *frmt_begin, va_list *args_begin)
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
}*/
