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

long double ft_find_whole(long double flt)
{
    t_bitld 	ld;
    int			tmp;

    ld.d = flt;
    if (!(ld.i >> 126 & 1))
	{
		tmp = ((ld.i) >> 64) & 0x3FFF; //- 0b011111111111111;
		if (tmp < 61)
			ld.i = (ld.i >> (62 - tmp)) << (62 - tmp);
		else if (tmp == 0x3FFF)
			ld.i = (ld.i >> (63)) << (63);
	}
	else
		return (0);
	return (ld.d);
}

int ft_find_whole_size(long double flt, long double *dec)
{
	int ret;

	*dec = .1;
	ret = 0;
	while (flt > 1.0)
	{
		ret++;
		*dec *= 10.0l;
		*dec = ft_find_whole(*dec);
		flt /= 10.0l;
	}
	return (ret == 0 ? 1 : ret);
}

int ft_push_whole(long double flt, long double dec, t_string **str, int sep)
{
	sep = sep > 3 ? sep : -1;
	if (dec < 0)
		return (1);
	if ((int)flt < 10 && (int)flt > -10 && dec < 1.0)
	{
		ft_string_push_back(str, (int) flt + '0');
		flt -= (int)flt;
	}
	while (dec >= 1.0)
	{
		if (sep > 0 && sep-- % 3 == 0)
			ft_string_push_back(str, FT_SEPARATOR);
		ft_string_push_back(str, (char)((int)(flt / ft_find_whole(dec)) + '0'));
		flt -= dec * (int)(flt / ft_find_whole(dec));
		dec /= 10.0l;
	}
}

double	ft_push_frctn(t_arg_data *ad, t_string **str, void *args)
{
    long double flt;
    long double fltw;
    long double dec;
    int p;

	fltw = ft_find_whole(*(((long double**)args)[0]));
	flt = (*((long double**)args)[0]) - fltw;
	p = ad->prcsn >= 0 ? ad->prcsn : DEF_F_PRCSN;
	if ((!p && dec > 0) || dec < 0)
		return (0);
	dec = .1;
	p++;
	while (--p)
	{
		flt *= 10l;
		dec *= 10.0l;
		dec = ft_find_whole(dec);
	}
	long double tm = flt - ft_find_whole(flt);
	flt += (flt - ft_find_whole(flt)) >= .5 ? 1 : 0; //TODO
	if ((int)(flt / ft_find_whole(dec)) >= 10)
	{
		fltw++;
		fltw /= ft_tolower(ad->frt) == 'e' ? 10 : 1;
		(*((int**)args)[2])++;
		*(((long double**)args)[1]) *= ft_tolower(ad->frt) == 'e' ? 1 : 10;
		flt = 0l;
	}
	ft_push_whole(fltw, *(((long double**)args)[1]), str,
			ad->spl ? *((int**)args)[2] : -1);
	ft_string_push_back(str, '.');
	ft_push_whole(flt, dec, str, -1);
}

int	ft_enot_s(long double *flt, t_string **str, long double *dec)
{
	int ret;


	*dec = 1.0;
	ret = 0;
	if (*flt == 0)
		return (ret);
	if (*flt >= 10)
		while (*flt > 10 && ++ret)
			*flt /= 10l;
	else
		while (*flt < 1 && --ret)
			*flt *= 10l;
	return (ret);
}

void ft_enot_e(t_string **str, int lg, char e)
{
	char buf[6];
	ft_string_push_back(str, e);
	ft_string_push_back(str, lg >= 0 ? '+' : '-');
	if (lg > 99)
		ft_string_push_back_s(str, ft_itoa_buf(FT_ABS(lg), buf));
	else
	{
		lg %= ft_string_push_back(str, (FT_ABS(lg) > 10) ? FT_ABS(lg) / 10 + '0'
														 : '0') * 10;
		ft_string_push_back(str, FT_ABS(lg) % 10 + '0');
	}
}

/*TODO ? solution differs from original printf on big number of digits because of
 * dividing by big value. Suppose that original one gets digits from the end but
 * not form the beggining of number as ours does. Should we fix this differ?*/
int ft_printf_float_compose(t_arg_data *ad, void *arg, t_string **str)
{
	long double flt;
	long double dec;
	long double dece;
	int lg;
	int lge;
	int pad;
	int pade;
	char nan;
	long double fltc;
	int prcsn;


	flt = ad->size == DEFAULT ? *(double *)arg : *(long double *) arg;
	nan = flt != flt || isinf(flt); //TODO repalce isinf to ft_isinf
	ad->sign = flt < 0 && !nan ? '-' : ad->sign;
	prcsn = ad->prcsn == DEFAULT ? DEF_F_PRCSN : ad->prcsn;
	flt *= flt < 0 ? -1 : 1;
	fltc = flt;
	lg = ft_find_whole_size(flt, &dec);
	lge = ft_enot_s(&fltc, str, &dece);
	pad = ad->wdth - lg - 1 - prcsn - (ad->sign != '\0') - lg / 3 * (ad->spl != '\0');
	pade = ad->wdth - 6 - (FT_ABS(lge) >= 100) - prcsn - (ad->sign != '\0');
	if (ad->frt == 'G' || ad->frt == 'g')
	{

		ad->frt = lge < -4 || lge > prcsn ? ad->frt - 'g' + 'e' : ad->frt - 'g' + 'f';
		pad = lge < -4 || lge > ad->wdth ? pade : pad;
		if (ad->prcsn == DEFAULT && ft_tolower(ad->frt) == 'f')
		{
			ad->wdth = lg;
			ad->prcsn = DEF_F_PRCSN - lg;
			pad += DEF_F_PRCSN - ad->prcsn;
		}
		else if (ad->prcsn == DEFAULT)
			ad->prcsn = 5;
	}
	if (ft_tolower(ad->frt) == 'e')
	{
		pad = pade;
		lg = lge;
		dec = dece;
		ft_enot_s(&flt, str, &dec);
	}
	pad = nan ? ad->wdth - 3 : pad;
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
	else
		ft_push_frctn(ad, str, (long double *[]){&flt, &dec, &lg});
	if (ft_tolower(ad->frt) == 'e' && !nan)
		ft_enot_e(str, lg, ad->frt);
	if (ad->l_a)
		ft_string_push_back_n_c(str, pad, ' ');
}
