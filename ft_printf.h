/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:40:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/18 14:38:55 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

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

t_arg_data ft_printf_parser(char **frmt, va_list *args, va_list args_begin);

int	ft_printf(const char *frmt, ...);
int ft_find_cntrl(const char **frmt, t_string **str);

#endif
