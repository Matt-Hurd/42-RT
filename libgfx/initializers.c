/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:49:17 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/18 06:37:08 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

void		free_all(t_data *d)
{
	int		y;
	t_list	*lst;
	t_list	*old;

	y = -1;
	while (++y < d->s->size.y)
		free(d->image[y]);
	lst = d->s->objects;
	while (lst)
	{
		old = lst;
		lst = lst->next;
		free(old->content);
		free(old);
	}
	free(d->s);
	free(d->input_thread);
}

t_vec3		*ft_make_vec3(float x, float y, float z)
{
	t_vec3 *ret;

	ret = (t_vec3 *)ft_memalloc(sizeof(t_vec3));
	ret->x = x;
	ret->y = y;
	ret->z = z;
	return (ret);
}

void		ft_set_vec3(t_vec3 *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

t_vertex	*ft_make_vertex(int x, int y, int z)
{
	t_vertex *ret;

	ret = (t_vertex *)ft_memalloc(sizeof(t_vertex));
	ret->local = ft_make_vec3(x, y, z);
	ret->world = ft_make_vec3(0, 0, 0);
	ret->aligned = ft_make_vec3(0, 0, 0);
	return (ret);
}
