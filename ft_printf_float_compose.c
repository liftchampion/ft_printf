/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float_compose.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:42:46 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/31 18:43:58 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <math.h>
#include "ft_printf_parser.h"

int ft_find_whole_size(long double flt, double *dec)
{
	int ret;

	*dec = .1;
	ret = 0;
	while (flt > 1.0)
	{
		ret++;
		*dec *= 10.0;
		flt /= 10.0;
	}
	return (ret);
}

int ft_push_whole(long double *flt, double dec, t_string **str)
{
	while (dec >= 1.0)
	{
		ft_string_push_back(str, (int)(*flt / dec) + '0');
		*flt -= dec * (int)(*flt / dec);
		dec /= 10.0;
	}
}

double	ft_simp_pow(double n, double *dec, int p)
{
	double ret;

	ret = n;
	while (--p)
	{
		ret *= n;
		*dec *= 10.0;
	}
	return (ret);
}

int ft_printf_float_compose(t_arg_data *arg_d, void *arg, t_string **str)
{
	long double flt;
	double dec;
	int log;

	if (arg_d->size == DEFAULT)
		flt = *(double *)arg;
	else
		flt = *(long double *) arg;
	log = ft_find_whole_size(flt, &dec);

	if (arg_d->width && !arg_d->l_a)
		ft_string_push_back_n_c(str, arg_d->width - log - 1 - arg_d->prcsn, arg_d->ac);
	ft_push_whole(&flt, dec, str);
	dec = 1.0;
	ft_string_push_back(str, '.');
	flt *= ft_simp_pow((double)10, &dec,
			arg_d->prcsn > 0 ? arg_d->prcsn : DEFAULT_F_PRECISION);
	flt += flt - (int)flt > .5 ? 1 : 0;
	ft_push_whole(&flt, dec, str);
	if (arg_d->l_a)
		ft_string_push_back_n_c(str, arg_d->width - log - 1 - arg_d->prcsn, ' ');
	flt *= pow(10, 6);
}
