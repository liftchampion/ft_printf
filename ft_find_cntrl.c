/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cntrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:03:08 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/18 14:58:58 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_find_cntrl(const char **frmt, t_string **str)
{
	while (**frmt != '%' && **frmt != '{')
	{
		if (!ft_string_push_back(str, **frmt))
			return (0);
		if (!**frmt)
			return (3);
		(*frmt)++;
	}
	(*frmt)++;
	if (*(*frmt - 1) == '%')
		return (1);
	else
		return (2);
}
