/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:06:26 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/23 15:07:29 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void			ft_print_string(t_string *str)
{
	if (!str)
	{
		ft_putstr("NO V_STRING\n");
		return ;
	}
	write(1, str->data, str->len);
	ft_putchar('\n');
}
