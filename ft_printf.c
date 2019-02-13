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
    str++;
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

t_string	*ft_vprintf(const char *frmt, va_list vl)
{
	t_string	*str[100];
	t_string	*args_seq;
	t_arg_data	*vars[99];

	args_seq = ft_make_string(32);
	str[0] = ft_make_string(64);
	vars[0] = 0;
	ft_loop(frmt, str, vars, args_seq);
	ft_stringify(&(str[0]), vars, vl, args_seq);
	free(args_seq);
	ft_free_string_arr(str, vars);
	return ((*str));
}

int ft_fdprintf(int fd, const char *frmt, ...)
{
	va_list		vl;
	t_string	*str;
	long int	ret;

	va_start(vl, frmt);
	str = ft_vprintf(frmt, vl);
	ft_fd_print_string(str, fd);
	ret = str ? str->len : -1;
	ft_free_string(&str);
	return ((int)ret);
}

int ft_printf(const char *frmt, ...)
{
	va_list		vl;
	t_string	*str;
	long int	ret;

	va_start(vl, frmt);
	str = ft_vprintf(frmt, vl);
	ft_print_string(str);
	ret = str ? str->len : -1;
	ft_free_string(&str);
	return ((int)ret);
}
