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

void ft_free_va_list_item_sizes(void)
{
	ft_get_va_list_item_by_idx(0, 0, 0, 0);
}

int ft_get_va_list_item_by_idx(va_list *args_begin, int idx, va_list *res,
											char *frmt_begin)
{
	static t_string *sizes = 0;
	int i;

	i = 0;
	if (args_begin == 0 && idx == 0 && res == 0 && *frmt_begin == 0)   /// 'close' sizes vector after end of printf
		ft_free_string(&sizes);
	if (sizes == 0 && idx != 0)
		if (!(sizes = ft_get_va_lst_sizes(frmt_begin)))
		{
			ft_free_string(&sizes);
			return (0);
		}
	va_copy(*res, *args_begin);
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

t_cntrl_cases ft_parse_arg_size_check_one_cntrl_block(char **frmt,
														t_string **sizes)
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
	int dont_add_va_lst_item;
	t_cntrl_cases curr_case;

	dont_add_va_lst_item = 0;
	while ((curr_case = ft_parse_arg_size_check_one_cntrl_block(frmt, sizes)))
	{
		if (curr_case == DONT_ADD_VA_LST_ITEM)
			dont_add_va_lst_item = 1;
	}
	return (dont_add_va_lst_item ? DONT_ADD_VA_LST_ITEM : NEUTRAL);
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



int ft_printf_is_size_specifier(char c)
{
	if (c == 'h' || c == 'l' || c == 'L' || c == 'j' || c == 'z')
		return (1);
	else
		return (0);
}

int ft_printf_is_simple_cntl(char c)
{
	if (c == ' ' || c == '+' || c == '-' || c == '0' || c == '#' || c == '\'')
		return (1);
	else
		return (0);
}

int ft_printf_is_cntl(char c)
{
	if (ft_isdigit(c) || c == '*' || c == ' ' || c == '+' || c == '-'
								|| c == '0' || c == '#' || c == '\'')
		return (1);
	else
		return (0);
}

// if (ft_strchr("diucCsSrpkfFeEgGxXob", c))

t_parse_len ft_printf_parse_size(char **frmt)
{
	static t_parse_len vars = (t_parse_len){INT, DOUBLE, 0, 0};
	t_parse_len ret;
	int curr_type;

	if (!frmt)
	{
		ret = vars;
		vars = (t_parse_len) {INT, DOUBLE, 0, 0};
		return (ret);
	}
	curr_type = ft_parse_len_specifier(frmt, &vars.was_two_h, &vars.was_two_l);
	if (curr_type == NONE)
		return (vars);
	if (curr_type <= LONG && ((t_int_lenghts)curr_type > vars.len_int
									|| (t_int_lenghts)curr_type == INT))
		vars.len_int = curr_type;
	else if (curr_type >= DOUBLE && (t_dbl_lenghts)curr_type > vars.len_dbl)
		vars.len_dbl = curr_type;
	return (vars);
}

void ft_printf_parse_simple_cntl(char c, t_arg_data *arg_data)
{
	if (c == ' ' || c == '+')
		arg_data->positive_sign = c;
	else if (c == '0')
		arg_data->allignment_char = c;
	else if (c == '-')
		arg_data->left_allignment = 1;
	else if (c == '#')
		arg_data->alternative_form = 1;
	else if (c == '\'')
		arg_data->apostrophe = 1;
}

int ft_printf_parse_simple_flags(char **frmt, t_arg_data *arg_data)
{
	int was_found;

	was_found = 0;
	while (ft_printf_is_simple_cntl(**frmt)
							|| ft_printf_is_size_specifier(**frmt))
	{
		was_found++;
		if (arg_data->was_dot)
		{
			arg_data->was_dot = 0;
			arg_data->precision = 0;
		}
		ft_printf_parse_size(frmt);
		ft_printf_parse_simple_cntl(**frmt, arg_data);
		(*frmt)++;
	}
	return (was_found ? 1 : 0);
}


void ft_printf_parse_star(char **frmt, t_arg_data *arg_data, va_list *args, t_begins *begins)
{
	int num;
	char *tmp;
	va_list arg;

	ft_printf_parse_simple_flags(frmt, arg_data);
	tmp = *frmt;
	if (ft_isdigit(*tmp) && *tmp != '0')
	{
		num = ft_atoi_m(&tmp);
		if (*tmp == '$')
		{
			ft_get_va_list_item_by_idx(begins->args_begin, num - 1, &arg,
					begins->frmt_begin);
			*frmt = tmp + 1;
		}
		else
			va_copy(arg, *args);
	}
	else
		va_copy(arg, *args);
	if (!arg_data->was_dot)
		arg_data->width = va_arg(arg, int);
	else
		arg_data->precision = va_arg(arg, int);
	arg_data->was_dot = 0;
}

void ft_printf_parse_num(char **frmt, t_arg_data *arg_data, t_begins *begins)
{
	int num;

	num = ft_atoi_m(frmt);
	ft_printf_parse_simple_flags(frmt, arg_data);
	if (**frmt == '$')
	{
		ft_get_va_list_item_by_idx(begins->args_begin, num - 1, arg_data->arg,
				begins->frmt_begin);
		(*frmt)++;
		return ;
	}
	if (arg_data->was_dot)
		arg_data->precision = num;
	else
		arg_data->width = num;

}

int ft_printf_parse_comp_flags(char **frmt, t_arg_data *arg_data, va_list *args, t_begins *begins)
{
	if (**frmt == '*')
	{
		(*frmt)++; // TODO think about \0
		ft_printf_parse_star(frmt, arg_data, args, begins);
		return (1);
	}
	else if (**frmt == '.')
	{
		arg_data->was_dot = 1;
		(*frmt)++;
		if (!((ft_isdigit(**frmt) && **frmt != '0') || **frmt == '*'))
		{
			arg_data->precision = 0;
			arg_data->was_dot = 0;
		}
		return (1);
	}
	else if (ft_isdigit(**frmt) && **frmt != '0')
	{
		ft_printf_parse_num(frmt, arg_data, begins);
		return (1);
	}
	return (0);
}


void ft_printf_print_arg_data(t_arg_data *arg_data)
{
	static int counter = 0;
	printf("%2d   width=%10d  prec=%10d  left_allign=%d  allign_char=<%c>  pos_sign=<%c>  alt_form=%d  apostrop=%d  "
		"int_len=%d  dbl_len=%d  char_arg=%d  format=%c\n",
			counter++, arg_data->width, arg_data->precision, arg_data->left_allignment, arg_data->allignment_char, arg_data->positive_sign,
			arg_data->alternative_form, arg_data->apostrophe, arg_data->int_size, arg_data->dbl_size, arg_data->char_arg, arg_data->format);
}

t_arg_data ft_printf_parser(char **frmt, va_list *args, char *frmt_begin, va_list *args_begin)
{
	t_arg_data *res;
	int was_found_flags;
	t_parse_len len_data;

	res = (t_arg_data*)ft_memalloc(sizeof(t_arg_data) * 1);
	*res = (t_arg_data){0, -1, 0, ' ', 0, 0, 0, 0, INT, DOUBLE, 0, 0, 0};
	res->precision = -1;
	while (**frmt)
	{
		was_found_flags = 0;
		was_found_flags += ft_printf_parse_simple_flags(frmt, res);
		was_found_flags += ft_printf_parse_comp_flags(frmt, res, args, &(t_begins){frmt_begin, args_begin});
		if (!was_found_flags)
			break ;
		///(*frmt)++;
	}
	len_data = ft_printf_parse_size(0);
	if (ft_strchr("diucCsSrpkfFeEgGxXob", **frmt)) // TODO move to other func
	{
		res->int_size = len_data.len_int;
		res->dbl_size = len_data.len_dbl;
		res->format = **frmt;
		res->arg = args;
		res->format = **frmt;
	}
	else
	{
		res->arg = 0;
		res->char_arg = **frmt;
		res->format = 'c';
	}
	ft_printf_print_arg_data(res);
}
