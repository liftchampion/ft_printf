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

#ifndef FT_PRINTF_PARSER_H
# define FT_PRINTF_PARSER_H

# include <stdarg.h>
# include "libft.h"

typedef enum 	e_int_lenghts
{
	CHAR_L = 1,
	SHORT_L = 2,
	INT_L = 3,
	LONG_LONG_L = 4,
	LONG_L = 5
}				t_int_lenghts;

typedef enum 	e_dbl_lenghts
{
	DOUBLE_L = 6,
	LD_L = 7
}				t_dbl_lenghts;

typedef enum 	e_cntrl_cases
{
	NO_CNTL = 0,
	NEUTRAL = 1,
	ADD_VA_LST_ITEM = 2,
	DONT_ADD_VA_LST_ITEM = 3
}				t_cntrl_cases;


typedef struct	s_parse_len
{
	t_int_lenghts len_int;
	t_dbl_lenghts len_dbl;
	int was_two_h;
	int was_two_l;
}				t_parse_len;

typedef struct	s_begins
{
	char *frmt_begin;
	va_list *args_begin;
}				t_begins;

int ft_string_set_value(t_string **str, size_t n, char filler, char value); // TODO move to another .h

int ft_get_va_list_item_by_idx(va_list *args_begin, int idx, va_list *res,
		char *frmt_begin);

t_string *ft_get_va_lst_sizes(char *frmt);

#endif
