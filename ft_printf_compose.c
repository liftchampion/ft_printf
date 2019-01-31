/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:40:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/27 04:20:43 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_parser.h"
#include "ft_printf_compose.h"
#include "ft_printf.h"
#include <stdio.h> // TODO delete

/*int ft_printf_string_compose(t_arg_data *arg_data, void *arg, t_string **str)
{

}*/

int ft_printf_float_compose(t_arg_data *arg_data, void *arg, t_string **str)
{
	printf("<%f>\n", *(double*)arg);
}

int ft_printf_get_itoa_radix(char c)
{
	if (ft_strchr("dDuUiI", c))
		return (10);
	else if (c == 'b' || c == 'B')
		return (c == 'b' ? 2 : -2);
	else if (c == 'o' || c == 'O')
		return (8);
	else if (c == 'x' || c == 'X' || c == 'p')
		return ((c == 'x' || c == 'p') ? -16 : 16);
	else
		return (10);
}

int ft_printf_int_compose(t_arg_data *arg_data, void* arg, t_string **str)
{
	char *res;
	char us;
	int radix;
	size_t len;
	int need_hex_prefix;

	us = ft_strchr("puUxXoObB", arg_data->format) != 0;
	radix = ft_printf_get_itoa_radix(arg_data->format);
	need_hex_prefix = (ft_strchr("xXp", arg_data->format) && ((*(int*)arg != 0
			&& arg_data->alternative_form) || arg_data->format == 'p')) ? 1 : 0;
	arg_data->width -= need_hex_prefix * 2;
	arg_data->prcsn += (arg_data->prcsn == 0) &&
			(ft_tolower(arg_data->format) == 'o') && arg_data->alternative_form;
	res = ft_printf_itoa_pro(ft_printf_int_caster(arg, arg_data->size, us,
							&arg_data->positive_sign), radix, arg_data);
	len = ft_strlen(res);
	if (!arg_data->left_allignment)
		ft_string_push_back_n_c(str, arg_data->width - len, arg_data->AC);
	if (need_hex_prefix)
		ft_string_push_back_s(str, arg_data->format == 'X' ? "0X" : "0x");
	ft_string_push_back_s(str, res);
	if (arg_data->left_allignment)
		ft_string_push_back_n_c(str, arg_data->width - len, arg_data->AC);
	free(res);
	return ((*str || !res) ? 1 : 0);
}

int ft_printf_string_compose(t_arg_data *arg_data, char **arg, t_string **str)
{
	size_t len;

	len = arg ? ft_strlen(arg) : 1;
	len = arg_data->prcsn < len ? arg_data->prcsn : len;
	if(!arg_data->left_allignment)
		ft_string_push_back_n_c(str, arg_data->width - len, arg_data->AC);
	ft_string_push_back_n_s(str, arg ? *arg : &arg_data->char_arg, len);
	if(arg_data->left_allignment)
		ft_string_push_back_n_c(str, arg_data->width - len, arg_data->AC);
}

// TODO get already tolowered type (fFg)
int ft_printf_compose(t_arg_data *arg_data, void *arg, t_string **str, char type)
{
	if (arg_data->width < 0)
	{
		arg_data->width *= -1;
		arg_data->left_allignment = 1;
	}
	if (type == 'g' && !ft_strchr("sScC", arg_data->format))
		return (ft_printf_int_compose(arg_data, arg, str));
	else if (type == 'g')
		return (ft_printf_string_compose(arg_data, (char**)arg, str));
	else
		return (ft_printf_float_compose(arg_data, arg, str));
	return (1);
}