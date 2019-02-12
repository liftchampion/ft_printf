/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:36:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/27 02:27:36 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_free_string_arr(t_string **str, t_arg_data **vars)
{
	while (*str)
	{
		ft_free_string(&(*str));
		str++;
	}
	while (*vars)
	{
		free(*vars);
		vars++;
	}
}

static int	ft_loop(const char *frmt, t_string **str, t_arg_data **vars,
		t_string *args_seq)
{
	int i;

	i = 0;
	while (*frmt)
	{
		if (!ft_find_cntrl(&frmt, &str[i]))
			return (-1);
		if (*(frmt - 1) == CLR_CNTRL && CLR)
		{
			if (ft_set_color(&frmt, &str[i]))
				return (-1);
			frmt += (*frmt != 0);
		}
		else
		{
			vars[i++] = ft_printf_parser(&frmt, &args_seq);
			vars[i] = 0;
			str[i] = ft_make_string(4);
			str[i + 1] = NULL;
		}
	}
}

int			ft_printf(const char *frmt, ...)
{
	va_list		vl;
	t_string	*str[100];
	t_string	*args_seq;
	t_arg_data	*vars[99];

	va_start(vl, frmt);
	args_seq = ft_make_string(32);
	str[0] = ft_make_string(64);
	vars[0] = 0;
	ft_loop(frmt, str, vars, args_seq);
	ft_stringify(&(str[0]), vars, vl, args_seq);
	ft_print_string(*str);
	free(args_seq);
	args_seq = (void*)str[0]->len;
	ft_free_string_arr(str, vars);
	va_end(vl);
	return ((int)args_seq > 0);
}
