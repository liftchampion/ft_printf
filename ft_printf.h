/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:40:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/24 18:38:45 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft/libft.h"  // TODO reset!!!!

typedef	enum	e_arg_sz
{
	CHAR = 1,
	SHORT = 2,
	LONG = 8,
	_INT128 = 16,
	DEFAULT = -2147481337
}				t_arg_sz;

/*
 * default precision for FP is 6
 * for GP is 1
 */

/**
 ** if 'width' or 'precision' field is negative
 **	it means, that you should use an arg indexed by abs() of this number
 **/

typedef struct	s_arg_data
{	
	int		width; /// negative only after *n$ be careful with left_alignment flag
	int 	precision;   /// -1 if wasn't changed
	char 	left_allignment; /// if width > 0 && left_alignment => width *= -1;
	char	allignment_char; /// char used for allignement default is ' '
	char	positive_sign; /// sign used for plus in positive numbers, default is \0 can be '+' or ' '
	char	alternative_form; /// #
	char 	apostrophe; /// '
	int 	num;
	t_arg_sz	size; /// Lenght of arg
	char 	char_arg;	/// for cases when type-specifier is wrong and need to print char
	char	format; // TODO d, f, F, e, E, g, G, x, X, o, s, c, p, b, r, k, C (lc), S
	char	__was_dot; // don't use! only for parsing
}				t_arg_data;

int				ft_printf(const char *frmt, ...);
int				ft_find_cntrl(const char **frmt, t_string **str);
int				ft_set_color(const char **frmt, t_string **str);
t_arg_data		*ft_printf_parser(char **frmt, t_string **args);

#endif
