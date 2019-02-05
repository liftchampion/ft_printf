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
	return (ret == 0 ? 1 : ret);
}

int ft_push_whole(long double *flt, double dec, t_string **str, int sep)
{
	sep = sep > 3 ? sep : -1;
	if (dec < 0)
		return (1);
	if ((int)*flt < 10 && (int)*flt > -10 && dec < 1.0)
	{
		ft_string_push_back(str, (int) *flt + '0');
		*flt -= (int)*flt;
	}
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
	if ((!p && dec > 0) || *dec < 0)
		return (0);
	ft_string_push_back(str, '.');
	*dec = .1;
	p++;
	while (--p)
	{
		*flt *= 10;
		*dec *= 10.0;
	}
	*flt += (*flt - (long long)*flt) > .5 ? 1 : 0;
	ft_push_whole(flt, *dec, str, -1);
}

int	ft_enot_s(long double *flt, t_string **str, double *dec)
{
	int ret;


	*dec = 1.0;
	ret = 0;
	if (*flt == 0)
		return (ret);
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
	ft_string_push_back(str, lg >= 0 ? '+' : '-');
	if (FT_ABS(lg) >= 100)
		lg %= ft_string_push_back(str, FT_ABS(lg) / 100 + '0') * 100;
	lg %= ft_string_push_back(str, (FT_ABS(lg) > 10) ? FT_ABS(lg) / 10 + '0' : '0') * 10;
	ft_string_push_back(str, FT_ABS(lg) % 10 + '0');
}

/*TODO ? solution differs from original printf on big number of digits because of
 * dividing by big value. Suppose that original one gets digits from the end but
 * not form the beggining of number as ours does. Should we fix this differ?*/
int ft_printf_float_compose(t_arg_data *ad, void *arg, t_string **str)
{
	long double flt;
	double dec;
	double dece;
	int lg;
	int pad;
	char nan;
	int lge;
	int pade;
	long double fltc;
	int prcsn;


	flt = ad->size == DEFAULT ? *(double *)arg : *(long double *) arg;
	nan = flt != flt || isinf(flt);
	ad->sign = flt < 0 && !nan ? '-' : ad->sign;
	flt *= flt < 0 ? -1 : 1;
	fltc = flt;
	lg = ft_find_whole_size(flt, &dec);
	lge = ft_enot_s(&fltc, str, &dece);
	pade = ad->wdth - 6 - (FT_ABS(lge) >= 100) - ad->prcsn - (ad->sign != '\0');
	pad = ad->wdth - lg - 1 - ad->prcsn - (ad->sign != '\0') - lg / 3 * (ad->spl != '\0');
	pad = nan ? ad->wdth - 3 : pad;
	if (ad->frt == 'G' || ad->frt == 'g')
	{
		prcsn = ad->prcsn == DEFAULT ? DEF_F_PRCSN : ad->prcsn;
		ad->frt = lge < -4 || lge > prcsn ? ad->frt - 'g' + 'e' : ad->frt - 'g' + 'f';
		pad = lge < -4 || lge > ad->wdth ? pade : pad;
		if (ad->prcsn == DEFAULT && ft_tolower(ad->frt) == 'e')
		{
			ad->wdth = lge;
			ad->prcsn = DEF_F_PRCSN - lge;
		}
	}
	else if (ft_tolower(ad->frt) == 'e')
	{
		pad = pade;
		lg = lge;
		dec = dece;
		ft_enot_s(&flt, str, &dec);
	}
	ad->ac = nan ? ' ' : ad->ac;
	if (ad->wdth && !ad->l_a)
	{
		if (ad->ac == '0')
		{
			ad->sign && flt == flt ? ft_string_push_back(str, ad->sign) : 0;
			ft_string_push_back_n_c(str, pad, ad->ac);
		}
		else
		{
			ft_string_push_back_n_c(str, pad, ad->ac);
			ad->sign && flt == flt ? ft_string_push_back(str, ad->sign) : 0;
		}
	}
	else
		ad->sign && flt == flt ? ft_string_push_back(str, ad->sign) : 0;
	if (nan && (ad->frt == 'e' || ad->frt == 'f'))
		dec = flt != flt ? ft_string_push_back_s(str, "nan") - 10000000 :
		ft_string_push_back_s(str, "inf") - 10000000;
	else if (nan && (ad->frt == 'E' || ad->frt == 'F'))
		dec = flt != flt ? ft_string_push_back_s(str, "NAN") - 10000000 :
			  ft_string_push_back_s(str, "INF") - 10000000;
	ft_push_whole(&flt, dec, str, ad->spl ? lg : -1);
	ft_push_frctn(&flt, &dec, ad->prcsn >= 0 ? ad->prcsn : DEF_F_PRCSN, str);
	if (ft_tolower(ad->frt) == 'e' && !nan)
		ft_enot_e(str, lg, ad->frt);
	if (ad->l_a)
		ft_string_push_back_n_c(str, pad, ' ');
}
