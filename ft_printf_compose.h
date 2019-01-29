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

#ifndef FT_PRINTF_COMPOSERS_H
# define FT_PRINTF_COMPOSERS_H

# include "ft_printf.h"

# ifdef AC
#  undef AC // Danger practice
# endif
# define AC allignment_char

char		*ft_printf_itoa_pro(__int128_t n, int rad, int prec, char sign);

void ft_print_bits(unsigned long n);

__int128_t ft_printf_int_caster(__int128_t n, t_arg_sz size, char us);

#endif
