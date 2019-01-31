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
#include "ft_printf.h"
#include <stdio.h> // TODO delete

/*int ft_printf_string_compose(t_arg_data *arg_data, void *arg, t_string **str)
{

}*/

int ft_printf_float_compose(t_arg_data *arg_data, void *arg, t_string **str)
{
	printf("<%f>\n", *(double*)arg);
}

int ft_printf_string_compose(t_arg_data *arg_data, char **arg, t_string **str)
{
	size_t len;
	char uni[5];

	len = arg ? ft_strlen(arg) : 1;
	len = arg_data->prcsn < len ? arg_data->prcsn : len;
	if(!arg_data->l_a)
		ft_string_push_back_n_c(str, arg_data->width - len, arg_data->ac);
	ft_bzero(uni, 5);
	if (ft_tolower(arg_data->format) == 'c')
		arg_data->format == 'C' ?
			ft_string_push_back_s(str, ft_int_to_unicode(*(int*)arg, uni))
			: ft_string_push_back(str, arg ? (char)*arg : arg_data->char_arg);
	else
		if (arg_data->format == 'S')
			while ((int*)arg++)
				ft_string_push_back_s(str, ft_int_to_unicode(*(int*)arg, uni));
		else
			ft_string_push_back_s(str, *arg);
	if(arg_data->l_a)
		ft_string_push_back_n_c(str, arg_data->width - len, arg_data->ac);
}

void ft_printf_final_arg_data_checks(t_arg_data *arg_data, char type)
{
	if (arg_data->width < 0 && (arg_data->l_a = 1))
		arg_data->width *= -1;
	if (type == 'g')
	{
		if (arg_data->prcsn == DEFAULT)
			arg_data->prcsn = (ft_tolower(arg_data->format) == 's') ?
					DEFAULT_STRING_PRECISION : DEFAULT_INT_PRECISION;
		else if (ft_tolower(arg_data->format) != 's')
			arg_data->ac = ' ';
		if (arg_data->ac == '0' && (ft_tolower(arg_data->format) != 's'))
		{
			arg_data->prcsn = arg_data->width;
			arg_data->width = 1;
		}
		if (arg_data->l_a)
			arg_data->ac = ' ';
	}
	else if (type == 'f' && arg_data->prcsn == DEFAULT)
			arg_data->prcsn = DEFAULT_FLOAT_PRECISION;
}

// TODO get already tolowered type (fFg)
int ft_printf_compose(t_arg_data *arg_data, void *arg, t_string **str, char type)
{
	ft_printf_final_arg_data_checks(arg_data, type);
	if (type == 'g' && !ft_strchr("sScC", arg_data->format))
		return (ft_printf_int_compose(arg_data, arg, str));
	else if (type == 'g')
		return (ft_printf_string_compose(arg_data, (char**)arg, str));
	else
		return (ft_printf_float_compose(arg_data, arg, str));
}