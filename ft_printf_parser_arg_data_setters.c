/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:40:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/16 23:44:33 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_parser.h"
#include "libft.h"

void			ft_printf_arg_data_set_width_or_prec(t_arg_data *arg_data,
																		int n)
{
	if (!arg_data->__was_dot)
	{
		arg_data->width = n;
	}
	else
	{
		arg_data->precision = n;
		arg_data->__was_dot = 0;
	}
}

t_arg_sz		ft_printf_parser_get_int_arg_size(char c, int lengths[4])
{
	if (ft_strchr(LONG_INT_TYPE_SPECS, c))
		return (LONG);
	else if ((c == 'c' && L_COUNT % 2) || c == 'C')
		return (DEFAULT);
	else if (c == 'c')
		return (CHAR);
	else if (_128_COUNT)
		return (_INT128);
	else if (L_COUNT)
		return (LONG);
	else if (H_COUNT % 2)
		return (SHORT);
	else if (H_COUNT)
		return (CHAR);
	else
		return (DEFAULT);
}

int				ft_set_int_arg_data(t_arg_data *arg_data, char c,
											t_string **args, int lengths[4])
{
	if (arg_data->precision == DEFAULT)
		arg_data->precision = DEFAULT_INT_PRECISION;
	arg_data->size = ft_printf_parser_get_int_arg_size(c, lengths);
	if (c == 'c' && arg_data->size == DEFAULT)
		arg_data->format = 'C';
	else
		arg_data->format = c;
	if (!ft_string_set_value(args, (size_t)(arg_data->num) - 1, 'g',
			arg_data->size == _INT128 ? (char)'G' : (char)'g'))
	{
		return (0);
	}
	return (1);
}

int				ft_set_float_arg_data(t_arg_data *arg_data, char c,
												t_string **args, int lengths[4])
{
	if (arg_data->precision == DEFAULT)
		arg_data->precision = DEFAULT_FLOAT_PRECISION;
	arg_data->size = BIG_L_COUNT ? LONG : DEFAULT;
	arg_data->format = c;
	if (!ft_string_set_value(args, (size_t)(arg_data->num) - 1, 'g',
			arg_data->size == LONG ? (char)'F' : (char)'f'))
	{
		return (0);
	}
	return (1);
}

void			ft_set_invalid_arg_data(t_arg_data *arg_data, char c,
																t_string **args)
{
	if (arg_data->precision == DEFAULT)
		arg_data->precision = DEFAULT_INT_PRECISION;
	arg_data->size = CHAR;
	arg_data->format = 'c';
	arg_data->char_arg = c;
	arg_data->num = -1;
	--(*args)->info;
}
