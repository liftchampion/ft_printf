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

# define DEFAULT_FLOAT_PRECISION 6
# define DEFAULT_INT_PRECISION 1

# define INT_TYPE_SPECIFIERS "dDiuUcCsSrpkxXoObB"
# define FLOAT_TYPE_SPECIFIERS "fFeEgG"
# define LONG_INT_TYPE_SPECS "sprkSDU"

# define SET_DEFAULT_LENGTHS lengths[0] = 0; lengths[1] = 0; lengths[2] = 0
# define _128_COUNT lengths[3]
# define H_COUNT lengths[2]
# define L_COUNT lengths[1]
# define BIG_L_COUNT lengths[0]

typedef struct	s_complex_flags_data
{
	int was_star;
	int num;
	int was_dollar;
	int was_zero;
}				t_complex_flags_data;

t_arg_data		*ft_printf_parser(char **frmt, t_string **args);
int				ft_printf_parse_simple_flags(char **frmt, t_arg_data *arg_data,
																int *lenghts);
int				ft_parse_len_specifier(char **frmt, int *lenghts);
int				ft_printf_parse_modifiers(char **frmt, t_arg_data *arg_data);
int				ft_printf_parse_comlex_flags(char **frmt, t_arg_data *arg_data,
												t_string **args, int *n_arg);
int				ft_printf_parser_comlex_flags_proceeder(t_arg_data *arg_data,
				t_complex_flags_data *flags_data, t_string **args, int *n_arg);
void			ft_printf_arg_data_set_width_or_prec(t_arg_data *arg_data,
																		int n);
t_arg_sz		ft_printf_parser_get_arg_size(char c, int lengths[4]);
int				ft_set_int_arg_data(t_arg_data *arg_data, char c,
											t_string **args, int lengths[4]);
int				ft_set_float_arg_data(t_arg_data *arg_data, char c,
											t_string **args, int lengths[4]);
void			ft_set_invalid_arg_data(t_arg_data *arg_data, char c,
															t_string **args);

#endif
