/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:47:48 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/24 00:04:37 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_color.h"

static char	ft_check_bgre(const char **frmt)
{
	char ret;

	ret = 0;
	if (*(*frmt) == 'b' && *(*frmt + 1) == '_')
	{
		*frmt += 2;
		ret += 10;
	}
	else if (*(*frmt) == 'r' && *(*frmt + 1) == '_')
	{
		*frmt += 2;
		ret += 1;
	}
	return (ret);
}

static int	ft_check_str(const char **frmt)
{
	int i;
	int j;

	i = -1;
	while (++i < NUM_OF_COLS)
	{
		j = 0;
		while (1)
		{
			if (!pf_cols[i].name[j])
				break ;
			if ((*frmt)[j] != pf_cols[i].name[j])
				break ;
			j++;
		}
		if (!pf_cols[i].name[j])
			break ;
	}
	*frmt += j;
	return (i);
}

static int	ft_parse_format(const char **frmt, t_string **str)
{
	char	bgre;
	int		i;

	bgre = ft_check_bgre(frmt);
	i = ft_check_str(frmt);
	if (i == NUM_OF_COLS)
		return ((ft_string_push_back_s(str, "0m") < 1) ? -1 : 0);
	bgre -= (pf_cols[i].num > 10 && bgre / 10 == 1) ? 10 : 0;
	bgre -= (pf_cols[i].num < 10 && bgre % 10 == 1) ? 1 : 0;
	bgre = (pf_cols[i].num == (char)0) ? (char)0 : bgre;
	return ((ft_string_push_back_s(str, ft_itoa(pf_cols[i].num + bgre +
						bgre % 10 * 20)) < 1) ? -1 : 1);
}

static int	ft_parse_compl_col(const char **frmt, t_string **str)
{
	if (*(++(*frmt)) == 'b' && *(*frmt + 1) == '_')
	{
		*frmt += 2;
		if (!ft_string_push_back_s(str, "48;5;"))
			return (-1);
	}
	else
	{
		if (!ft_string_push_back_s(str, "38;5;"))
			return (-1);
	}
	while (ft_isdigit(**frmt))
	{
		if (ft_string_push_back(str, *((*frmt)++)) < 1)
			return (-1);
	}
	return (1);
}

t_res_item	*ft_set_color(const char **frmt)
{
	int			ret;
	t_string	*str;
	t_res_item	*res_item;

	if (!frmt || !*frmt || !(str = ft_make_string(1))) // TODO free it
		return (0);
	ft_string_push_back_s(&str, "\e[");
	while (**frmt && **frmt != '}')
	{
		if (*(*frmt) == '\\')
		{
			if (ft_parse_compl_col(frmt, &str) < 1)
				return (0);
		}
		else if ((ret = ft_parse_format(frmt, &str)) < 1)
			return (0);
		if (**frmt != ',')
			break ;
		else if (!(*frmt)++ || !ft_string_push_back(&str, ';'))
			return (0);
	}
	if (**frmt)
		(*frmt)++;
	ft_string_push_back_s(&str, "m");
	if (!(res_item = (t_res_item*)malloc(sizeof(t_res_item))))
		return (0);
	*res_item = (t_res_item){str->data, 0, I_COLOR};
	ft_memdel((void**)&str);
	return (res_item);
}
