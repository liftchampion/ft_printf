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

int			ft_find_whole_size(long double flt, long double *dec)
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

long double	ft_find_whole(long double flt)
{
	t_bitld		ld;
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

void		ft_dog(t_fc *fc, t_arg_data *ad)
{
	long double	dp;
	int			i;
	int			lp;

	lp = -1;
	i = 0;
	dp = fc->f;
	while (++i <= ad->prcsn)
	{
		dp *= 10.l;
		lp = (ft_find_whole(dp) != 0) ? i : lp;
		dp -= ft_find_whole(dp);
	}
	ad->prcsn = lp == -1 ? 0 : lp;
}

void		ft_tor(t_fc *fc, t_arg_data *ad)
{
	long double	cp;
	int			i;

	cp = fc->f;
	i = ad->prcsn + 1;
	fc->f_d = 0.1l;
	fc->f_lg = 0;
	while (i-- && (fc->f_d *= 10.l))
		cp = (cp - ft_find_whole(cp)) * 10.l;
	fc->f += (cp > 5.l) ? 1.l / fc->f_d : 0.l;
	if (fc->f > 1.l)
	{
		fc->f -= 1.l;
		fc->w += 1.l;
		fc->w_lg += (ft_tolower(ad->frt) == 'e' || ft_tolower(ad->frt) == 'g')
			? (fc->w >= 10.l && (fc->w /= 10.l)) : (fc->w / fc->w_d >= 10.l);
		fc->w_d *= (fc->w / fc->w_d >= 10.l) ? 10.l : 1.l;
	}
	if (ft_tolower(ad->frt) == 'e')
		fc->w_d = 1;
}

void		ft_enot(t_fc *fc)
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
