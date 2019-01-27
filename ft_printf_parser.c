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
#include "ft_printf_parser.h"
#include "libft.h"

#include <stdlib.h>

///															TODO delete it
#include <stdio.h>

void			ft_printf_print_arg_data(t_arg_data *arg_data)
{
	static int counter = 0;

	printf("%2d   width=%4d  prec=%4d  left_allign=%d  allign_char=<%c>  "
		"pos_sign=<%c>  alt_form=%d  apostrop=%d  "
		"ARG_IDX=%2d  size=%11d  char_arg=%2d  format=%c\n",
			counter++, arg_data->width, arg_data->precision,
			arg_data->left_allignment, arg_data->allignment_char,
			arg_data->positive_sign, arg_data->alternative_form,
			arg_data->apostrophe, arg_data->num, arg_data->size,
			arg_data->char_arg, arg_data->format);
}
///															TODO delete it

t_arg_data		*ft_printf_parser_flags_proceeder(const char **frmt, t_string **args,
														int lengths[4])
{
	t_arg_data	*arg_data;
	int			was_found_flag;

	++(*args)->info;
	SET_DEFAULT_LENGTHS;
	_128_COUNT = 0;
	if (!(arg_data = (t_arg_data*)malloc(sizeof(t_arg_data))))
		return (0);
	*arg_data =
			(t_arg_data){0, 1, DEFAULT, 0, ' ', 0, 0, 0, 0, DEFAULT, -1, 0, 0};
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
		{
			ft_memdel((void**)&arg_data);
			return (0);
		}
	}
	else if (ft_strchr(FLOAT_TYPE_SPECIFIERS, **frmt) && **frmt)
	{
		if (!ft_set_float_arg_data(arg_data, *(*frmt)++, args, lengths))
		{
			ft_memdel((void**)&arg_data);
			return (0);
		}
	}
	else if (**frmt)
		ft_set_invalid_arg_data(arg_data, *(*frmt)++, args);
	ft_printf_print_arg_data(arg_data); // TODO delete it
	return (arg_data);
}
