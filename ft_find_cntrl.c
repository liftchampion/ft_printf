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

int	ft_find_cntrl(const char **frmt, t_string **str)
{
	if (!frmt || !*frmt || !str || !*str)
		return (0);
	while (**frmt != '%' && (**frmt != '{' && *(*frmt - 1) != '\\'))
	{
		if (!ft_string_push_back(str, **frmt))
			return (0);
		(*frmt)++;
	}
	(*frmt)++;
		return (1);
}
