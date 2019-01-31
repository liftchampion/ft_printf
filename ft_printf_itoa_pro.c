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

#include <stdlib.h>
#include "ft_printf.h"

char			*ft_printf_get_bits(unsigned long n, t_arg_data *ad)
{
	int			len;
	char		*ret;
	int			i;
	t_arg_sz	sz;
	char		f;

	sz = ad->size;
	f = ad->spl ? ad->spl : (char)' ';
	i = 0;
	sz = (sz == DEFAULT) ? 4 : sz;
	len = sz * 8;
	len += sz - 1;
	if (!(ret = ft_memalloc(sizeof(char) * (len + 1))))
		return (0);
	len -= (sz - 1) + 1;
	while (len >= 0)
	{
		ret[i++] = (char)'0' + ((n & (1L << len)) != 0);
		if (len && len % 8 == 0)
			ret[i++] = f;
		len--;
	}
	return (ret);
}

unsigned long	ft_printf_int_caster(void *n, t_arg_sz sz, char us, char *sign)
{
	if (sz == CHAR && (us || ((*(char*)n < 0 && (*sign = '-'))) ||
															(*(char*)n >= 0)))
		return (us ? *(unsigned char*)n :
					(unsigned char)(*(char*)n * (1 - 2 * (*sign == '-'))));
	else if (sz == SHORT && (us || ((*(short*)n < 0 && (*sign = '-'))) ||
															(*(short*)n >= 0)))
		return (us ? *(unsigned short*)n :
					(unsigned short)(*(short*)n * (1 - 2 * (*sign == '-'))));
	else if (sz == DEFAULT && (us || ((*(int*)n < 0 && (*sign = '-'))) ||
															(*(int*)n >= 0)))
		return (us ? *(unsigned int*)n :
					(unsigned int)(*(int*)n * (1 - 2 * (*sign == '-'))));
	else if (sz == LONG && (us || ((*(long*)n < 0 && (*sign = '-'))) ||
															(*(long*)n >= 0)))
		return (us ? *(unsigned long*)n :
					(unsigned long)(*(long*)n * (1 - 2 * (*sign == '-'))));
	else
		return (*(unsigned long*)n);
}

char			*ft_printf_itoa_pro(unsigned long n, int r, t_arg_data *ad)
{
	static char		bas[] = "0123456789ABCDEF";
	int				l;
	char			*ret;
	unsigned long	nb;
	int				i;

	if (r == -2)
		return (ft_printf_get_bits(n, ad));
	if (r == 16 || r == -16)
		(r < 0 && (r *= -1)) ? ft_tolower_str(bas) : ft_toupper_str(bas);
	l = 1 + (n != 0) + (ad->sign && r == 10);
	nb = n;
	while (nb >= r && l++)
		nb /= r;
	l += ((l - 2) / 3) * ((i = 1) && ad->spl != 0 && (r == 10 || r == 8));
	l = (ad->prcsn + 1 > l) ? (ad->prcsn + 1 + (ad->sign && r == 10)) : l;
	if (!(ret = (char *)ft_memalloc(sizeof(char) * l--)))
		return (NULL);
	while ((n || l) && (ret[--l] = bas[(n % r)]))
		if (((n /= r) + 1) && n && !(i++ % 3) && ad->spl && (r == 10 || r == 8))
			ret[--l] = ad->spl;
	ret[0] = (ad->sign && r == 10) ? ad->sign : ret[0];
	return (ret);
}

int ft_printf_get_itoa_radix(char c)
{
	if (ft_strchr("dDuUiI", c))
		return (10);
	else if (c == 'b' || c == 'B')
		return (c == 'b' ? 2 : -2);
	else if (c == 'o' || c == 'O')
		return (8);
	else if (c == 'x' || c == 'X' || c == 'p')
		return ((c == 'x' || c == 'p') ? -16 : 16);
	else
		return (10);
}

int ft_printf_int_compose(t_arg_data *arg_data, void* arg, t_string **str)
{
	char *res;
	char us;
	int radix;
	size_t len;
	int need_hex_prefix;

	us = ft_strchr("puUxXoObB", arg_data->format) != 0;
	radix = ft_printf_get_itoa_radix(arg_data->format);
	need_hex_prefix = (ft_strchr("xXp", arg_data->format) && ((*(int*)arg != 0
			&& arg_data->alt) || arg_data->format == 'p')) ? 1 : 0;
	arg_data->width -= need_hex_prefix * 2;
	arg_data->prcsn += (arg_data->prcsn == 0) &&
			(ft_tolower(arg_data->format) == 'o') && arg_data->alt;
	res = ft_printf_itoa_pro(ft_printf_int_caster(arg, arg_data->size, us,
			&arg_data->sign), radix, arg_data);
	len = ft_strlen(res);
	if (!arg_data->l_a)
		ft_string_push_back_n_c(str, arg_data->width - len, arg_data->ac);
	if (need_hex_prefix)
		ft_string_push_back_s(str, arg_data->format == 'X' ? "0X" : "0x");
	ft_string_push_back_s(str, res);
	if (arg_data->l_a)
		ft_string_push_back_n_c(str, arg_data->width - len, arg_data->ac);
	free(res);
	return ((*str || !res) ? 1 : 0);
}
