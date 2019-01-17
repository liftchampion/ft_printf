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

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef enum	e_printf_arg_sizes
{
	B1,
	B2,
	B4,
	B8,
	B16
}				t_printf_arg_sizes;

typedef enum 	e_int_lenghts
{
	NONE,
	CHAR,
	SHORT,
	INT,
	LONG_LONG,
	SIZE,
	LONG
}				t_int_lenghts;

typedef enum 	e_dbl_lenghts
{
	DOUBLE,
	LD
}				t_dbl_lenghts;

typedef struct	s_arg_data
{
	int		wdth;
	int 	prcson;
	char	allgnmnt_chr;
	char	pstv_sgn;
	char	altrntv_form;
	va_list arg;
	char	format;				// TODO d, f, F, e, E, g, G, x, X, o, s, c, p, b, r, k
}				t_arg_data;

t_arg_data ft_printf_parser(char **frmt, va_list *args, char *frmt_begin, va_list *args_begin);

int	ft_printf(const char *frmt, ...);

va_list *ft_get_va_list_item_by_idx(va_list *args_begin, int idx);

t_string *ft_get_va_lst_sizes(char *frmt);

#endif
