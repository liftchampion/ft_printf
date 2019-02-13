/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/01/27 04:24:31 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_parser.h"

#include <stdlib.h>

t_arg_data		*ft_printf_parser_flags_proceeder(const char **frmt,
		t_string **args, int lengths[4])
{
	t_arg_data	*arg_data;
	int			was_found_flag;

	++(*args)->info;
	SET_DEFAULT_LENGTHS;
	_128_COUNT = 0;
	if (!(arg_data = (t_arg_data*)malloc(sizeof(t_arg_data))))
		return (0);
	*arg_data =
			(t_arg_data){0, DEFAULT, 0, ' ', 0, 0, 0, 0, DEFAULT, 0, 0, 0};
	was_found_flag = 1;
	while (was_found_flag)
	{
		was_found_flag = 0;
		was_found_flag += ft_printf_parse_simple_flags(frmt, arg_data, lengths);
		was_found_flag += ft_printf_parse_comlex_flags(frmt, arg_data, args,
				&(*args)->info);
		if ((*args)->info == -1)
		{
			ft_memdel((void**)&arg_data);
			return (0);
		}
	}
	arg_data->num = (*args)->info;
	return (arg_data);
}

t_arg_data		*ft_printf_parser(const char **frmt, t_string **args)
{
	t_arg_data	*arg_data;
	int			lengths[4];

	if (!(arg_data = ft_printf_parser_flags_proceeder(frmt, args, lengths)))
		return (0);
	if (ft_strchr(INT_TYPE_SPECIFIERS, **frmt) && **frmt)
	{
		if (!ft_set_int_arg_data(arg_data, *(*frmt)++, args, lengths))
			ft_memdel((void**)&arg_data);
	}
	else if (ft_strchr(FLOAT_TYPE_SPECIFIERS, **frmt) && **frmt)
	{
		if (!ft_set_float_arg_data(arg_data, *(*frmt)++, args, lengths))
			ft_memdel((void**)&arg_data);
	}
	else if (**frmt)
		ft_set_invalid_arg_data(arg_data, *(*frmt)++, args);
	return (arg_data);
}
