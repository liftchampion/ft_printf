/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 03:00:46 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/27 04:24:46 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_stringify(t_string **str, t_arg_data *v[], va_list vl, t_string *a_s)
{
	int i;

	i = 0;
	while (1)
	{
		if (!str || !str[i] || !*str)
			return ;
		if ((v[i])->format == 0)
			return ;
		if (v[i]->width < 0)
			v[i]->width = *(int*)ft_get_va((v[i]->width + 1) * -1, vl, a_s);
		if (v[i]->prcsn < 0)
			v[i]->prcsn = *(int*)ft_get_va((v[i]->prcsn + 1) * -1, vl, a_s);
		if (v[i]->char_arg)
			ft_gen_compose(v[i], NULL, str);
		else if (ft_tolower(a_s->data[v[i]->num - 1]) == 'g')
			ft_gen_compose(v[i], ft_get_va(v[i]->num - 1, vl, a_s), str);
		else
			ft_float_compose(v[i], ft_get_va(v[i]->num - 1, vl, a_s), str);
		i++;
		ft_string_push_back_s(str, str[i]->data);
	}
}
