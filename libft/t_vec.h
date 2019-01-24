/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 13:41:24 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/15 00:08:06 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VEC_H
# define T_VEC_H
# include "libft.h"

typedef struct		s_vector2
{
	int		x;
	int		y;
}					t_vec2;

typedef struct		s_vector3
{
	int		x;
	int		y;
	int		z;
}					t_vec3;

typedef struct		s_vector3_f
{
	float		x;
	float		y;
	float		z;
}					t_vec3_f;

typedef struct		s_vector4
{
	int	x;
	int	y;
	int	z;
	int	color;
}					t_vec4;

typedef struct		s_vector
{
	void			*data;
	unsigned int	cap;
	unsigned int	len;
	unsigned int	offset;
}					t_vector;

t_vector			*ft_vecinit(size_t cap);
void				ft_vecdel(void **vect);
t_vector			*ft_vecpush(t_vector *vec, void *data, size_t s);
t_vector			*ft_vecgrow(t_vector *vec, size_t s);
t_vector			*ft_vecshrink(t_vector *vec, unsigned int offset);

typedef struct		s_string
{
	char		*data;
	size_t		len;
	size_t		capacity;
	int			info;
}					t_string;

void				ft_print_string(t_string *str);

void				ft_free_string(t_string **str);

int					ft_string_fit(t_string **str);

int					ft_string_push_back(t_string **str, char c);

int					ft_string_set_value(t_string **str, size_t n, char filler,
																	char value);

t_string			*ft_make_string(size_t init_size);

#endif
