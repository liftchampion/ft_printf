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
#define FT_SEPARATOR ','
#define CLR_CNTRL '{'
#define CLR 0

typedef	enum	e_arg_sz
{
	CHAR = 1,
	SHORT = 2,
	LONG = 8,
	_INT128 = 16,
	DEFAULT = -2147481337,
}				t_arg_sz;

# define _128_SPECIFIER '_'

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
	int		wdth; /// 									just push_n chars
	int 	prcsn;   /// 								push_n '0'
	char 	l_a; /// 						when to push width
	char	ac; ///						before pushing number push ' '/'+' (also -1 to width/prec)
	char	sign; /// sign used for plus in positive numbers, default is \0 can be '+' or ' '
	char	alt; /// #
	char 	spl; /// '
	int 	num;
	t_arg_sz	size; /// Lenght of arg
	char 	char_arg;	/// for cases when type-specifier is wrong and need to print char
	char	frt; // TODO d, D, u, U, f, F, e, E, g, G, x, X, o, s, c, p, b, B, r, k, C (lc), S
	char	__was_dot; // don't use! only for parsing
}				t_arg_data;

int				ft_printf(const char *frmt, ...);
int				ft_find_cntrl(const char **frmt, t_string **str);
int				ft_set_color(const char **frmt, t_string **str);
t_arg_data		*ft_printf_parser(const char **frmt, t_string **args);
void			ft_stringify(t_string **str, t_arg_data *v[], va_list vl,
		t_string *a_s);
void			ft_free_string_arr(t_string *str[], int i);
void			*ft_get_va(int num, va_list vl, t_string *a_s);
void			ft_gen_compose(t_arg_data *v, void *num, t_string **str);
int				ft_printf_float_compose(t_arg_data *ad, void *n, t_string **str);
int				ft_printf_compose(t_arg_data *ad, void *arg,
		t_string **str, char type);
int				ft_printf_int_compose(t_arg_data *ad, void* arg,
		t_string **str);
int				ft_printf_string_compose(t_arg_data *ad, char **a,
		t_string **str);

#endif
