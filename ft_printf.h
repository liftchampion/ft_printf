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

typedef enum 	e_int_lenghts
{
	NONE = 0,
	CHAR = 1,
	SHORT = 2,
	INT = 3,
	LONG_LONG = 4,
	SIZE = 5,
	LONG = 6
}				t_int_lenghts;

typedef enum 	e_dbl_lenghts
{
	DOUBLE = 7,
	LD = 8
}				t_dbl_lenghts;

typedef enum 	e_cntrl_cases
{
	NO_CNTL = 0,
	NEUTRAL = 1,
	ADD_VA_LST_ITEM = 2,
	DONT_ADD_VA_LST_ITEM = 3
}				t_cntrl_cases;

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

int ft_get_va_list_item_by_idx(va_list args_begin, int idx, va_list *res,
		char *frmt_begin);

t_string *ft_get_va_lst_sizes(char *frmt);

#endif
