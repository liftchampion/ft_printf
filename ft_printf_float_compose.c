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

int ft_push_whole(long double *flt, double dec, t_string **str, int sep)
{
	sep = sep > 3 ? sep : -1;
	while (dec >= 1.0)
	{
		if (sep > 0 && sep-- % 3 == 0)
			ft_string_push_back(str, FT_SEPARATOR);
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
/*TODO ? solution differs from original printf on big number of digits because of
 * dividing by big value. Suppose that original one gets digits from the end but
 * not form the beggining of number as ours does. Should we fix this differ?*/
int ft_printf_float_compose(t_arg_data *arg_d, void *arg, t_string **str)
{
	long double flt;
	double dec;
	int log;
	int pad;

	if (arg_d->size == DEFAULT)
		flt = *(double *)arg;
	else
		flt = *(long double *) arg;
	log = ft_find_whole_size(flt, &dec);

	pad = arg_d->width - log - arg_d->prcsn - (arg_d->sign == '+') - log / 3;
	if (arg_d->sign)
		ft_string_push_back(str, arg_d->sign);
	if (arg_d->width && !arg_d->l_a)
		ft_string_push_back_n_c(str, pad, arg_d->ac);
	ft_push_whole(&flt, dec, str, arg_d->spl ? log : -1);
	dec = 1.0;
	ft_string_push_back(str, '.');
	flt *= ft_simp_pow((double)10, &dec,
			arg_d->prcsn > 0 ? arg_d->prcsn : DEFAULT_F_PRECISION);
	flt += flt - (long long)flt > .5 ? 1 : 0;
	ft_push_whole(&flt, dec, str, -1);
	if (arg_d->l_a)
		ft_string_push_back_n_c(str, arg_d->width - log - 1 - arg_d->prcsn, ' ');
	flt *= pow(10, 6);
}
