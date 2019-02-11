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

#include "ft_printf_parser.h"
#include "ft_printf.h"
#include <stdio.h> // TODO delete

/*int ft_guf(int *str, int prec)
{
	int p;

	p = 0;
	while (*str && prec > ft_unilen(*str) - 1)
	{
		p += ft_unilen(*str);
		prec -= ft_unilen(*str);
		str++;
	}
	return (p);
}

int ft_printf_string_compose(t_arg_data *ad, char **a, t_string **str)
{
	size_t ln;
	char uni[5];
	static char *n = "(null)";

	a = a && !*a && ft_tolower(ad->frt) == 's' && (ad->frt = 's') ? &n : a;
	ln = a && ft_tolower(ad->frt) == 's' ? ft_strlen_u(*a, ad->frt == 's') : 1;
	ln = a && ad->frt == 'C' ? ft_unilen(*(int*)a) : ln;
	ln = ad->frt == 's' && ad->prcsn < ln ? ad->prcsn : ln;
	ln = ad->frt == 'S' && ad->prcsn < ln ? ft_guf(*(int**)a, ad->prcsn) : ln;
	ad->frt = ad->frt == 'C' && !*(int*)a ? (char)'c' : ad->frt;
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - ln, ad->ac);
	if (ft_tolower(ad->frt) == 'c')
		ad->frt == 'C' ? ft_string_push_back_s(str, ft_int_to_unicode(*(int*)a,
				uni)) : ft_string_push_back(str, a ? (char)*a : ad->char_arg);
	else
		if (ad->frt == 'S')
			while (**(int**)a && ad->prcsn > ft_unilen(*(int*)*a) - 1 &&
						(*a += 4))
				ad->prcsn -= ft_string_push_back_s(str,
						ft_int_to_unicode(*(int*)(*a - 4), uni));
		else
			ad->prcsn >= 0 ? ft_string_push_back_n_s(str, *a,
					ad->prcsn) : ft_string_push_back_s(str, *a);
	if(ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - ln, ad->ac);
	return (*str ? 1 : 0);
}*/

int ft_print_hex_float_compose(t_arg_data *ad, void *arg, t_string **str)
{

}

void ft_printf_final_arg_data_checks(t_arg_data *ad, char type)
{
	if (ad->wdth < 0 && (ad->l_a = 1))
		ad->wdth *= -1;
	if (type == 'g')
	{
		if (ad->prcsn == DEFAULT)
			ad->prcsn = (ft_strchr("sSr", ad->frt)) ?
						DEFAULT_STRING_PRECISION : DEFAULT_INT_PRECISION;
		else if (!ft_strchr("cCsSr", ad->frt))
			ad->ac = ' ';
		if (ad->l_a)
			ad->ac = ' ';
		if (ad->ac == '0' && !ft_strchr("cCsSr", ad->frt))
		{
			ad->prcsn = ad->wdth ? ad->wdth : 1;
			ad->wdth = -1;
		}
	}
	else if (type == 'f')
	{
		if (ad->prcsn == DEFAULT)
			ad->prcsn = ft_tolower(ad->frt) == 'g' ? DEFAULT : DEF_F_PRCSN;
		if (ad->prcsn == 0)
			ad->prcsn = ft_tolower(ad->frt) == 'g' ? 1 : 0;
	}
}

// TODO set 'g'/'G' prec to 1 if zero
int ft_printf_compose(t_arg_data *ad, void *arg, t_string **str, char type)
{
	ft_printf_final_arg_data_checks(ad, type);
	if (type == 'g' && !ft_strchr("sSncCr", ad->frt))
		return (ft_printf_int_compose(ad, arg, str));
	else if (type == 'g' && ad->frt == 'n')
		return ((**(int**)arg = (int)(*str)->len) * 0 + 1);
	else if (type == 'f' && (ft_tolower(ad->frt) == 'a'))
		return (ft_printf_hex_float_compose(ad, arg, str));
	else if (type == 'g')
		return (ft_printf_string_compose(ad, (char**)arg, str));
	else
		return (ft_printf_float_compose(ad, arg, str));
}