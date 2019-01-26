/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cntrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:03:08 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/23 19:41:15 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_res_item *ft_find_cntrl(const char **frmt)
{
	int			was_slash;
	size_t		len;
	char		*str_begin;
	t_res_item	*res;

	was_slash = 0;
	len = 0;
	str_begin = 0;
	if (!frmt || !*frmt)
		return (0);
	str_begin = (char*)*frmt;
	while (**frmt && **frmt != '%' && (**frmt != '{' && !was_slash))
	{
		was_slash = **frmt == '\\' ? 1 : 0;
		(*frmt)++;
		len++;
	}
	if (**frmt)
		(*frmt)++;
	if (!(res = (t_res_item*)malloc(sizeof(t_res_item))))
		return (0);
	*res = (t_res_item){str_begin, len, I_STRING};
	return (res);
}
