/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cntrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:03:08 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/18 15:30:52 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_find_cntrl(const char **frmt, t_string **str)
{
	while (**frmt != '%' && **frmt != '{')
	{
		if (!ft_string_push_back(str, **frmt))
			return ((char) -1);
		(*frmt)++;
	}
	(*frmt)++;
		return (*(*frmt - 1));
}
