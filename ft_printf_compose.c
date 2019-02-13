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
		if (ad->l_a || ad->frt == 'k')
			ad->ac = ' ';
		if (ad->ac == '0' && !ft_strchr("cCsSrk", ad->frt))
		{
			ad->prcsn = ad->wdth ? ad->wdth : 1;
			ad->wdth = -1;
		}
	}
	else if (type == 'f')
	{
		if (ad->prcsn == DEFAULT)
			ad->prcsn = DEF_F_PRCSN;
		if (ad->prcsn == 0)
			ad->prcsn = ft_tolower(ad->frt) == 'g' ? 1 : 0;
	}
}

// TODO set 'g'/'G' prec to 1 if zero
int ft_printf_compose(t_arg_data *arg_data, void *arg, t_string **str, char type)
{
	ft_printf_final_arg_data_checks(arg_data, type);
	if (type == 'g' && !ft_strchr("sScCrk", arg_data->frt))
		return (ft_printf_int_compose(arg_data, arg, str));
	else if (type == 'g' && !ft_strchr("kn", arg_data->frt))
		return (ft_printf_string_compose(arg_data, (char**)arg, str));
	else if (type == 'g' && arg_data->frt == 'k')
		return (ft_printf_date_compose(arg_data, arg, str));
	else if (type == 'g' && arg_data->frt == 'n')
		; // TODO n_compose
	else if (type == 'f')
		return (ft_printf_float_compose(arg_data, arg, str));
}