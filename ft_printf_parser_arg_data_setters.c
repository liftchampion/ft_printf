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

t_arg_sz		ft_printf_parser_get_arg_size(char c, int lengths[2])
{
	if (ft_strchr(FLOAT_TYPE_SPECIFIERS, c))
	{
		if (lengths[1] == LD_L)
			return (LONG);
		else
			return (DEFAULT);
	}
	else
	{
		if (c == 'D')
			return (_INT128);
		else if (ft_strchr(LONG_INT_TYPE_SPECS, c))
			return (LONG);
		else if ((c == 'c' && lengths[0] == LONG_L) || c == 'C')
			return (DEFAULT);
		else if (lengths[0] == CHAR_L || c == 'c')
			return (CHAR);
		else if (lengths[0] == SHORT_L)
			return (SHORT);
		else if (lengths[0] == LONG_L || lengths[0] == LONG_LONG_L)
			return (LONG);
		else
			return (DEFAULT);
	}
}

int				ft_set_int_arg_data(t_arg_data *arg_data, char c,
											t_string *args, int lengths[2])
{
//TODO maybe need to use ANOTHER DEFAULT WIDTH for o x b
	if (arg_data->precision == DEFAULT)
		arg_data->precision = DEFAULT_INT_PRECISION;
	arg_data->size = ft_printf_parser_get_arg_size(c, lengths);
	if (c == 'c' && arg_data->size == DEFAULT)
		arg_data->format = 'C';
	else
		arg_data->format = c;
	if (!ft_string_set_value(&args, (size_t)(arg_data->num) - 1, 'g',
			arg_data->size == _INT128 ? (char)'G' : (char)'g'))
	{
		return (0);
	}
	return (1);
}

int				ft_set_float_arg_data(t_arg_data *arg_data, char c,
												t_string *args, int lengths[2])
{
	if (arg_data->precision == DEFAULT)
		arg_data->precision = DEFAULT_FLOAT_PRECISION;
	arg_data->size = ft_printf_parser_get_arg_size(c, lengths);
	arg_data->format = c;
	if (!ft_string_set_value(&args, (size_t)(arg_data->num) - 1, 'g',
			arg_data->size == LONG ? (char)'F' : (char)'f'))
	{
		return (0);
	}
	return (1);
}

void			ft_set_invalid_arg_data(t_arg_data *arg_data, char c,
																t_string *args)
{
	if (arg_data->precision == DEFAULT)
		arg_data->precision = DEFAULT_INT_PRECISION;
	arg_data->size = CHAR;
	arg_data->format = 'c';
	arg_data->char_arg = c;
	arg_data->num = -1;
	--args->info;
}
