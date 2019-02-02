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

//TODO refactor to reduce number of functions or move some of them to another file

//TODO check for safety!!!

//TODO rounding of when precision is 0

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
		ft_string_push_back(str, (char)((int)(*flt / dec) + '0'));
		*flt -= dec * (int)(*flt / dec);
		dec /= 10.0;
	}
}

double	ft_push_frctn(long double *flt, double *dec, int p, t_string **str)
{
	if (!p)
		return (0);
	ft_string_push_back(str, '.');
	*dec = .1;
	while (p--)
	{
		*flt *= 10;
		*dec *= 10.0;
	}
	*flt += *flt - (long long)*flt > .5 ? 1 : 0;
	ft_push_whole(flt, *dec, str, -1);
}

int	ft_enot_s(long double *flt, t_string **str, double *dec)
{
	int ret;

	if (*flt != *flt)
		*dec = ft_string_push_back_s(str, "nan") - 10000000;
	if (isinf(*flt))
		*dec = ft_string_push_back_s(str, "inf") - 10000000;
	*dec = 1.0;
	ret = 0;
	if (*flt >= 10)
		while (*flt > 10 && ++ret)
			*flt /= 10;
	else
		while (*flt < 1 && --ret)
			*flt *= 10;
	return (ret);
}

void ft_enot_e(t_string **str, int lg, char e)
{
	ft_string_push_back(str, e);
	ft_string_push_back(str, lg > 0 ? '+' : '-');
	if (FT_ABS(lg) >= 100)
		ft_string_push_back(str, FT_ABS(lg) / 100 + '0');
	ft_string_push_back(str, (FT_ABS(lg) > 10) ? FT_ABS(lg) / 10 + '0' : '0');
	ft_string_push_back(str, lg % 10 + '0');
}

/*TODO ? solution differs from original printf on big number of digits because of
 * dividing by big value. Suppose that original one gets digits from the end but
 * not form the beggining of number as ours does. Should we fix this differ?*/
int ft_printf_float_compose(t_arg_data *a_d, void *arg, t_string **str)
{
	long double flt;
	double dec;
	int lg;
	int pad;

	flt = a_d->size == DEFAULT ? *(double *)arg : *(long double *) arg;
	flt < 0 ? ft_string_push_back(str, '-') : 0;
	flt *= flt < 0 ? -1 : 1;
	lg = ft_find_whole_size(flt, &dec);
	if (a_d->sign)
		ft_string_push_back(str, a_d->sign);
	pad = ft_tolower(a_d->format) == 'e' ? a_d->width - lg - a_d->prcsn -
			 (a_d->sign == '+') - lg / 3 : a_d->width - 6 - a_d->prcsn;
	if (a_d->width && !a_d->l_a)
		ft_string_push_back_n_c(str, pad, a_d->ac);
	lg = ft_tolower(a_d->format) == 'e' ? ft_enot_s(&flt, str, &dec) : lg;
	ft_push_whole(&flt, dec, str, a_d->spl ? lg : -1);
	ft_push_frctn(&flt, &dec, a_d->prcsn >= 0 ? a_d->prcsn : DEF_F_PRCSN, str);
	if (ft_tolower(a_d->format) == 'e')
		ft_enot_e(str, lg, a_d->format);
	if (a_d->l_a)
		ft_string_push_back_n_c(str, a_d->width - lg - 1 - a_d->prcsn, ' ');
}
