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

#define PUSH_S ft_string_push_back_s
#define PUSH_C ft_string_push_back
#define PUSH_NC ft_string_push_back_n_c
#define PUSH_NS ft_string_push_back_n_s


int ft_guf(int *str, int prec)
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

int ft_printf_string_compose(t_arg_data *ad, char **a, t_string **str) // TODO check null
{
	size_t ln;
	char uni[5];
	static char *n = "(null)";

	a = !*a && ft_tolower(ad->frt) == 's' /*&& (ad->frt = 's')*/ ? &n : a;
	ad->frt = a == &n ? (char)'s' : ad->frt;
	ln = ft_tolower(ad->frt) == 's' ? ft_strlen_u(*a, ad->frt == 's') : 1;
	ln = ad->frt == 'C' ? ft_unilen(*(int*)a) : ln;
	ln = ad->frt == 's' && ad->prcsn < ln ? ad->prcsn : ln;
	ln = ad->frt == 'S' && ad->prcsn < ln ? ft_guf(*(int**)a, ad->prcsn) : ln;
	ad->frt = ad->frt == 'C' && !*(int*)a ? (char)'c' : ad->frt;
	if (!ad->l_a)
		PUSH_NC(str, ad->wdth - ln, ad->ac);
	if (ft_tolower(ad->frt) == 'c')
		ad->frt == 'C' ? PUSH_S(str, ft_int_to_unicode(*(int*)a, uni)) :
												PUSH_C(str, (char)*a);
	else if (ad->frt == 'S')
		while (**(int**)a && ad->prcsn > ft_unilen(*(int*)*a) - 1 && (*a += 4))
			ad->prcsn -= PUSH_S(str,
					ft_int_to_unicode(*(int*)(*a - 4), uni));
	else
		ad->prcsn >= 0 ? PUSH_NS(str, *a, ad->prcsn) : PUSH_S(str, *a);
	if (ad->l_a)
		PUSH_NC(str, ad->wdth - ln, ad->ac);
	return (*str ? 1 : 0);
}
