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
#include "ft_printf_parser.h"
#include <math.h>

void		ft_push_part(t_fc *fc, int prc, t_string **str)
{
	int i;

	i = 0;
	if (prc == -1)
	{
		while (fc->w_d >= 1.0)
		{
			ft_string_push_back(str, (char)((int)(fc->w / fc->w_d) + '0'));
			fc->w -= fc->w_d * (int)(fc->w / fc->w_d);
			fc->w_d /= 10.0;
		}
	}
	else
	{
		while (i++ < prc)
		{
			fc->f *= 10.l;
			ft_string_push_back(str, (char)((int)fc->f + '0'));
			fc->f -= ft_find_whole(fc->f);
		}
	}
}

void		ft_push_all(t_fc *fc, t_arg_data *ad, t_string **str)
{
	int		pad;
	char	buf[10];

	buf[0] = '0';
	pad = (ad->sign != 0) + ((ft_tolower(ad->frt) == 'e') ?
			(3 + ft_intlen(FT_ABS(fc->w_lg)) + (fc->w_lg > -10 && fc->w_lg < 10)
			+ (ad->prcsn != 0 || ad->alt) + ad->prcsn)
			: (fc->w_lg + 1 + (ad->prcsn != 0 || ad->alt) + ad->prcsn));
	ft_string_push_back((ad->sign && ad->ac == '0') ? str : 0, ad->sign);
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - pad, ad->ac);
	ft_string_push_back((ad->sign && ad->ac == ' ') ? str : 0, ad->sign);
	ft_push_part(fc, -1, str);
	ft_string_push_back((ad->prcsn || ad->alt) ? str : 0, '.');
	ft_push_part(fc, ad->prcsn, str);
	if (ft_tolower(ad->frt) == 'e')
	{
		ft_string_push_back(str, ad->frt);
		ft_string_push_back(str, fc->w_lg >= 0 ? (char)'+' : (char)'-');
		fc->w_lg = FT_ABS(fc->w_lg);
		ft_string_push_back_s(str, ft_itoa_buf(fc->w_lg, buf +
			(fc->w_lg < 10)) - (fc->w_lg < 10));
	}
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - pad, ad->ac);
}

int			ft_check_nan(long double *n, t_arg_data *ad, t_string **str)
{
	int		is_nan;
	int		is_inf;
	t_bitld	bts;

	bts.d = *n;
	is_nan = *n != *n;
	is_inf = isinf(*n);
	ad->sign = ((bts.i >> 79 & 1) ? (char)'-' : ad->sign) * !is_nan;
	ad->prcsn = (ad->prcsn > 4000) ? 4000 : ad->prcsn;
	*n = (*n < 0.0l) ? (-1.0l * *n) : *n;
	if (!is_inf && !is_nan)
		return (0);
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - (3 + (ad->sign != 0)), ' ');
	ft_string_push_back(ad->sign ? str : 0, ad->sign);
	if (ad->frt > 'Z')
		ft_string_push_back_s(str, is_nan ? "nan" : "inf");
	else
		ft_string_push_back_s(str, is_nan ? "NAN" : "INF");
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - (3 + (ad->sign != 0)), ' ');
	return (1);
}

int			ft_get_exp(t_fc fc, t_arg_data *ad)
{
	ft_enot(&fc);
	ft_tor(&fc, ad);
	return ((fc.w_lg ? fc.w_lg : fc.f_lg));
}

t_fc		*ft_fc_maker(t_arg_data *ad, long double *arg)
{
	t_fc	*dt;
	int		exp;

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
		exp = ft_get_exp(*dt, ad);
		ad->frt = ad->frt - 'g' + ((exp < -4 || exp >= ad->prcsn) ? 'e' : 'f');
		ad->prcsn -= ft_tolower(ad->frt) == 'e' ? 1 :
				dt->w_lg + (dt->w_lg == 0);
	}
	if (ft_tolower(ad->frt) == 'e')
		ft_enot(dt);
	ft_tor(dt, ad);
	if (ad->was_dot)
		ft_dog(dt, ad);
	return (dt);
}
