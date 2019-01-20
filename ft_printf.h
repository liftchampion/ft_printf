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

typedef enum 	e_arg_types
{
	CHAR_T,
	U_CHAR_T,
	WCHAR_T,
	SHORT_T,
	U_SHORT_T,
	INT_T,
	U_INT_T,
	LONG_T,
	U_LONG_T,
	DOUBLE_T,
	LONG_DOUBLE_T,
	STRING_T,
	W_STRING_T
	// TODO finish if needed
}				t_arg_types;


typedef struct	s_parse_len
{
	t_int_lenghts len_int;
	t_dbl_lenghts len_dbl;
	int was_two_h;
	int was_two_l;
}				t_parse_len;

typedef struct	s_parse_cntl
{
	t_int_lenghts len_int;
	t_dbl_lenghts len_dbl;
	char was_dot;
}				t_parse_cntl;

typedef struct	s_begins
{
	char *frmt_begin;
	va_list *args_begin;
}				t_begins;

typedef struct	s_arg_data
{
	int		width;
	int 	precision;   /// -1 if wasn't changed
	char 	left_allignment;
	char	allignment_char;
	char	positive_sign;
	char	alternative_form;
	char 	apostrophe;
	va_list *arg;
	t_arg_types arg_type;
	char 	char_arg;
	char	format; // TODO d, f, F, e, E, g, G, x, X, o, s, c, p, b, r, k
	char	was_dot;
}				t_arg_data;

t_arg_data ft_printf_parser(char **frmt, va_list *args, char *frmt_begin, va_list *args_begin);

int	ft_printf(const char *frmt, ...);

int ft_get_va_list_item_by_idx(va_list *args_begin, int idx, va_list *res,
		char *frmt_begin);

t_string *ft_get_va_lst_sizes(char *frmt);

#endif
