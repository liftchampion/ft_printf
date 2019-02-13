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

int ft_find_whole_size(long double flt, long double *dec)
{
	int ret;

	*dec = 1;
	ret = 0;
	if (flt == 0 || flt == 1)
	{
		ret = 0;
	}
	else if (flt > 1.l)
		while (flt > 10.0l)
		{
			ret++;
			*dec *= 10.0;
			flt /= 10.0;
		}
	else if (flt < 1.l)
		while (flt < 1.0l)
		{
			ret--;
			*dec /= 10.0;
			flt *= 10.0;
		}
	return (ret);
}

typedef union   u_bitld
{
	long double d;
	__uint128_t i;
	unsigned long is[2];
}               t_bitld;

long double ft_find_whole(long double flt)
{
	t_bitld 	ld;
	int			tmp;

	if (flt < 1.l && flt > -1.l)
		return (0);
	ld.d = flt;
	if ((ld.i >> 78 & 1) || (int)(((ld.i) >> 64) & 0x3FFF))
	{
		tmp = (int)(((ld.i) >> 64) & 0x3FFF);
		if (tmp < 61)
			ld.i = (ld.i >> (62 - tmp)) << (62 - tmp);
		else if (tmp == 0x3FFF)
			ld.i = (ld.i >> (63)) << (63);
	}
	else
		return (0);
	return (ld.d);
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
	if (isinf(*flt)) // TODO use ft_isinf
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



typedef struct	s_fc
{
	long double w;
	long double w_d;
	long double f;
	long double f_d;
	int f_lg;
	int w_lg;
}				t_fc;

void ft_push_part(t_fc *fc, int prc, t_string **str)
{
	int i;

	i = 0;
	if (prc == -1)
	{
		while (fc->w_d >= 1.0)
		{
			ft_string_push_back(str, (char) ((int) (fc->w / fc->w_d) + '0'));
			fc->w -= fc->w_d * (int) (fc->w / fc->w_d);
			fc->w_d /= 10.0;
		}
	}
	else
	{
		while (i++ < prc)
		{
			fc->f *= 10.l;
			ft_string_push_back(str, (char) ((int)fc->f + '0'));
			fc->f -= ft_find_whole(fc->f);
		}
	}
}

void ft_push_all(t_fc *fc, t_arg_data *ad, t_string **str)
{
	int pad;
	char buf[10];

	buf[0] = '0';
	pad = (ad->sign != 0) + (ft_tolower(ad->frt) == 'e') ? (3 + ft_intlen(fc->w_lg) - (fc->w_lg < 0) + (fc->w_lg > -10 && fc->w_lg < 10) + (ad->prcsn != 0 || ad->alt) + ad->prcsn)
			: (fc->w_lg + (ad->prcsn != 0 || ad->alt) + ad->prcsn);
	if (ad->sign && ad->ac == '0')
		ft_string_push_back(str, ad->sign);
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - pad, ad->ac);
	if (ad->sign && ad->ac == ' ')
		ft_string_push_back(str, ad->sign);
	ft_push_part(fc, -1, str);
	if (ad->prcsn || ad->alt)
		ft_string_push_back(str, '.');
	ft_push_part(fc, ad->prcsn, str);
	if (ft_tolower(ad->frt) == 'e')
	{
		ft_string_push_back(str, ad->frt);
		ft_string_push_back(str, fc->w_lg >= 0 ? (char)'+' : (char)'-');
		fc->w_lg = FT_ABS(fc->w_lg);
		ft_string_push_back_s(str, ft_itoa_buf(fc->w_lg, buf + (fc->w_lg < 10)) - (fc->w_lg < 10));
	}
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - pad, ad->ac);
}

int ft_check_nan(long double *n, t_arg_data *ad, t_string **str)
{
	int is_nan;
	int is_inf;

	is_nan = *n != *n;
	is_inf = isinf(*n); // TODO use ft_isinf
	ad->sign = ((*n < 0.0l) ? (char)'-' : ad->sign) * !is_nan; // TODO use bits for check for -0
	ad->prcsn = (ad->prcsn > 4000) ? 4000 : ad->prcsn;
	*n = (*n < 0.0l) ? (-1.0l * *n) : *n;
	if (!is_inf && !is_nan)
		return (0);
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - (3 + (ad->sign != 0)), ' ');
	ft_string_push_back(ad->sign ? str : 0, ad->sign);
	if (ad->frt > 'Z')
		ft_string_push_back_s(str, is_nan ? "nan" : "inf");
	else
		ft_string_push_back_s(str, is_nan ? "NAN" : "INF");
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - (3 + (ad->sign != 0)), ' ');
	return (1);
}

void ft_dog(t_fc *fc, t_arg_data *ad)
{
	long double dp;
	int i;
	int lp;

	lp = -1;
	i = 0;
	dp = fc->f;
	while (i++ <= ad->prcsn)
	{
		dp *= 10.l;
		lp = (ft_find_whole(dp) != 0) ? i - 1 : lp;
		dp -= ft_find_whole(dp);
	}
	ad->prcsn = lp == -1 ? 0 : lp;
}

void ft_tor(t_fc *fc, t_arg_data *ad)
{
	long double cp;
	int i;

	cp = fc->f;
	i = ad->prcsn + 1;
	fc->f_d = 0.1l;
	fc->f_lg = 0;
	while (i-- && ++fc->f_lg)
	{
		cp -= ft_find_whole(cp);
		cp *= 10.l;
		fc->f_d *= 10.l;
		//fc->f_d = ft_find_whole(fc->f_d); // TODO no need ?
	}
	fc->f += cp > 5.l ? 1.l / fc->f_d : 0.l;
	if (fc->f > 1.l)
	{
		fc->f -= 1.l;
		fc->w += 1.l;
		fc->w_lg += (ft_tolower(ad->frt) == 'e') ? (fc->w >= 10.l &&
							(fc->w /= 10.l)) : (fc->w / fc->w_d >= 10.l);
		fc->w_d *= (fc->w / fc->w_d >= 10.l) ? 10.l : 1.l;
	}
	if (ft_tolower(ad->frt) == 'e')
		fc->w_d = 1;
}

void ft_enot(t_fc *fc)
{
	long double cp;

	if (fc->w == 0)
	{
		cp = fc->f / fc->f_d;
		fc->w = ft_find_whole(cp);
		fc->f = cp - fc->w;
		fc->w_lg = fc->f_lg;
	}
	else
	{
		cp = fc->w / fc->w_d;
		fc->w = ft_find_whole(cp);
		fc->f = fc->f / fc->w_d + (cp - fc->w);
	}
}

t_fc *ft_fc_maker(t_arg_data *ad, long double *arg)
{
	t_fc *dt;
	int exp;

	if (!(dt = (t_fc*)ft_memalloc(sizeof(t_fc))))
		return (0);
	dt->w = ft_find_whole(*arg);
	dt->f = *arg - dt->w;
	dt->w_lg = ft_find_whole_size(dt->w, &dt->w_d);
	dt->f_lg = ft_find_whole_size(dt->f, &dt->f_d);
	ad->was_dot = 0;
	if (ft_tolower(ad->frt) == 'g')
	{
		ad->was_dot = 1;
		exp = (dt->w_lg ? dt->w_lg : dt->f_lg);
		ad->frt = ad->frt - 'g' + (exp < -4 || exp >= ad->prcsn) ? 'e' : 'g';
		ad->prcsn -= ft_tolower(ad->frt) == 'e' ? 1 : dt->w_lg + (dt->w_lg == 0);
	}
	if (ft_tolower(ad->frt) == 'e')
		ft_enot(dt);
	ft_tor(dt, ad);
	if (ad->was_dot)
		ft_dog(dt, ad);
	return (dt);
}

char *ft_f_compose(t_fc *fc, t_arg_data *ad)
{
	t_string *buf;

	if (!(buf = ft_make_string(64)))
		return (0);

}

void ft_print_fc(t_fc *fc)
{
	printf("---------\nw   = %.20Lf\nwd  = %.20Lf\nw_lg= %d\nf   = %.20Lf\nfd  = %.20Lf\nf_lg= %d\n---------\n",
			fc->w, fc->w_d, fc->w_lg, fc->f, fc->f_d, fc->f_lg);
}

int ft_printf_float_compose(t_arg_data *ad, void *arg, t_string **str)
{
	long double flt;
	double dec;
	int lg;
	int pad;
	t_fc *dt;

	flt = ad->size == DEFAULT ? *(double*)arg : *(long double*) arg;
	if (ft_check_nan(&flt, ad, str))
		return (*str ? 1 : 0);
	if (!(dt = ft_fc_maker(ad, &flt)))
		return (0);
	//ft_print_fc(dt);
	ft_push_all(dt, ad, str);
	return (*str ? 1 : 0);


	/*lg = ft_find_whole_size(flt, &dec);
	if (ad->sign)
		ft_string_push_back(str, ad->sign);
	pad = ft_tolower(ad->frt) == 'e' ? ad->wdth - lg - ad->prcsn -
			 (ad->sign == '+') - lg / 3 : ad->wdth - 6 - ad->prcsn;
	if (ad->wdth && !ad->l_a)
		ft_string_push_back_n_c(str, pad, ad->ac);
	lg = ft_tolower(ad->frt) == 'e' ? ft_enot_s(&flt, str, &dec) : lg;
	ft_push_whole(&flt, dec, str, ad->spl ? lg : -1);
	ft_push_frctn(&flt, &dec, ad->prcsn >= 0 ? ad->prcsn : DEF_F_PRCSN, str);
	if (ft_tolower(ad->frt) == 'e')
		ft_enot_e(str, lg, ad->frt);
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - lg - 1 - ad->prcsn, ' ');*/
}
