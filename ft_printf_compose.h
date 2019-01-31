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



char		*ft_printf_itoa_pro(unsigned long n, int rad, t_arg_data *ad);

void ft_print_bits(unsigned long n);

unsigned long ft_printf_int_caster(void* n, t_arg_sz size, char us, char *sign);

#endif
