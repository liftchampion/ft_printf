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

static void ft_vl_to_p(va_list vl, t_string *a_s, void *vl_p[])
{
	int i;

	i = -1;
	while ((a_s->data)[++i])
	{
		if (a_s->data[i] == 'F')
		{
			// TODO correct_work_with_paddings
			///vl->overflow_arg_area = (size_t)vl->overflow_arg_area % 16 ? \
					vl->overflow_arg_area + 8 : vl->overflow_arg_area;
			vl_p[i] = vl->overflow_arg_area;
			va_arg(vl, long double);
		}
		else if (a_s->data[i] == 'f')
		{
			vl_p[i] = (vl->fp_offset < 176) ? vl->reg_save_area + vl->fp_offset
					: vl->overflow_arg_area;
			va_arg(vl, double);
		}
		else
		{
			vl_p[i] = (vl->fp_offset < 48) ? vl->reg_save_area + vl->gp_offset
											: vl->overflow_arg_area;
			va_arg(vl, long);
		}
	}
}

void ft_stringify(t_string **str, t_arg_data *v[], va_list vl, t_string *a_s)
{
	int i;
	va_list vlc;
	void	**vl_p;

	i = 0;
	vl_p = malloc(sizeof(void *) * a_s->len);
	ft_vl_to_p(vl, a_s, vl_p);
	while (1)
	{
		if (!str || !str[i] || !*str || v[i]->format == 0)
			return ;
		if (v[i]->width < 0)
			v[i]->width = *(int*)vl_p[i];
		if (v[i]->prcsn < 0)
			v[i]->prcsn = *(int*)vl_p[i] >= 0 ? *(int*)vl_p[i] : 1;  // todo added ternary for  > 1
		/*if (v[i]->char_arg)
			ft_gen_compose(v[i], NULL, str);
		else if (ft_tolower(a_s->data[v[i]->num - 1]) == 'g')
			ft_gen_compose(v[i], vl_p[i], str);
		else
			ft_float_compose(v[i], vl_p[i], str);*/
		i++;
		ft_string_push_back_s(str, str[i]->data);
	}
}
