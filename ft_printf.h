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

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"
# define FT_SEPARATOR ','
# define CLR_CNTRL '{'
# define CLR 1

# define PUSH_S ft_string_push_back_s
# define PUSH_C ft_string_push_back
# define PUSH_NC ft_string_push_back_n_c
# define PUSH_NS ft_string_push_back_n_s

typedef	enum	e_arg_sz
{
	CHAR = 1,
	SHORT = 2,
	LONG = 8,
	_INT128 = 16,
	DEFAULT = -2147481337,
}				t_arg_sz;

# define _128_SPECIFIER '_'

typedef struct	s_arg_data
{
	int			wdth;
	int			prcsn;
	char		l_a;
	char		ac;
	char		sign;
	char		alt;
	char		spl;
	int			num;
	t_arg_sz	size;
	char		char_arg;
	char		frt;
	char		was_dot;
}				t_arg_data;

int				ft_printf(const char *frmt, ...);
int				ft_find_cntrl(const char **frmt, t_string **str);
int				ft_set_color(const char **frmt, t_string **str);
t_arg_data		*ft_printf_parser(const char **frmt, t_string **args);
int				ft_stringify(t_string **str, t_arg_data *v[], va_list vl,
		t_string *a_s);
void			*ft_get_va(int num, va_list vl, t_string *a_s);
void			ft_gen_compose(t_arg_data *v, void *num, t_string **str);
int				ft_printf_float_compose(t_arg_data *ad, void *n,
		t_string **str);
int				ft_printf_compose(t_arg_data *arg_dat, void *arg,
		t_string **str, char type);
int				ft_printf_int_compose(t_arg_data *ad, void *arg,
		t_string **str);
int				ft_printf_string_compose(t_arg_data *ad, char **a,
		t_string **str);
int				ft_printf_date_compose(t_arg_data *ad, void *arg,
		t_string **str);

#endif
