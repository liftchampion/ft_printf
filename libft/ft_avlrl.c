/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avlrr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:30:48 by ehugh-be          #+#    #+#             */
/*   Updated: 2018/12/07 02:35:56 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btavl	*ft_avlrl(t_btavl *tr)
{
	t_btavl *tmp;

	if (!tr)
		return (NULL);
	tmp = tr->right;
	tr->right = tmp->left;
	tmp->left = tr;
	ft_avlfixh(tmp);
	ft_avlfixh(tr);
	return (tmp);
}
