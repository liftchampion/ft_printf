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

#include "ft_printf_compose.h"
#include "ft_printf.h"

int ft_printf_string_compose(t_arg_data *arg_data, void *arg, t_string **str)
{

}

int ft_printf_float_compose(t_arg_data *arg_data, void *arg, t_string **str)
{

}

int ft_printf_int_compose(t_arg_data *arg_data, void *arg, t_string **str)
{

}



// TODO get already tolowered type
int ft_printf_compose(t_arg_data *arg_data, void *arg, t_string **str, char type)
{
	if (type == 'g' && !ft_strchr("sScC", arg_data->format))
		return (ft_printf_int_compose(arg_data, arg, str));
	else if (type == 'g')
		return (ft_printf_string_compose(arg_data, arg, str));
	else
		return (ft_printf_float_compose(arg_data, arg, str));
}