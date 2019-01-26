/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cntrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:03:08 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/27 02:12:38 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_find_cntrl(const char **frmt, t_string **str)
{
	char slash;

	if (!str || !*str)
		return (0);
	slash = 0;
	while (**frmt && **frmt != '%' && (**frmt != '{' && !slash))
	{
		slash = (**frmt == '\\') ? 1 : 0;
		if (!ft_string_push_back_c(str, **frmt))
			return (0);
		(*frmt)++;
	}
	if (**frmt)
		(*frmt)++;
	return (1);
}
