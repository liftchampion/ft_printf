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

int ft_printf_string_compose(t_arg_data *arg_data, void *arg, t_string **str)
{

}

int ft_printf_float_compose(t_arg_data *arg_data, void *arg, t_string **str)
{

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
		return (c == 'x' ? 16 : -16);
	else
		return (10);
}

int ft_printf_int_compose(t_arg_data *arg_data, long arg, t_string **str)
{
	char *res;
	char us;
	int radix;
	size_t len;

	us = ft_strchr("puUxXoObB", arg_data->format) != 0;
	radix = ft_printf_get_itoa_radix(arg_data->format);

	if (!(res = ft_printf_itoa_pro(ft_printf_int_caster(arg, arg_data->size,
			us), radix, arg_data->prcsn, arg_data->positive_sign)))
		return (0);
	len = ft_strlen(res);
	if (!arg_data->left_allignment)
		if (!ft_string_push_back_n_c(str, arg_data->width - len, arg_data->AC))
			return (0);
	///if (ft_strchr("xXp", arg_data->format) && arg != 0)
	if (!ft_string_push_back_s(str, res))
		return (0);
	if (arg_data->left_allignment)
		if (!ft_string_push_back_n_c(str, arg_data->width - len, arg_data->AC))
			return (0);
	return (1);
}



// TODO get already tolowered type (fFg)
int ft_printf_compose(t_arg_data *arg_data, void *arg, t_string **str, char type)
{
	if (type == 'g' && !ft_strchr("sScC", arg_data->format))
		return (ft_printf_int_compose(arg_data, *(long*)arg, str));
	else if (type == 'g')
		return (ft_printf_string_compose(arg_data, arg, str));
	else
		return (ft_printf_float_compose(arg_data, arg, str));
}