/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 20:39:50 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/22 21:44:05 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normal_sphere(t_ray *r, t_sphere *s, t_vec3 *n)
{
	sub_vect(&r->start, &s->props.pos, n);
	normalize_vector(n);
}

int		intersect_sphere(t_ray *r, t_sphere *s, float *t)
{
	int		retval;
	t_vec3	*dist;
	t_vec3	temp;
	float	discr;

	retval = 0;
	temp.x = dot_vect(&r->dir, &r->dir);
	dist = (t_vec3 *)ft_memalloc(sizeof(t_vec3));
	sub_vect(&r->start, &s->props.pos, dist);
	temp.y = 2 * dot_vect(&r->dir, dist);
	temp.z = dot_vect(dist, dist) - (s->radius * s->radius);
	free(dist);
	discr = temp.y * temp.y - 4 * temp.x * temp.z;
	if (discr < 0)
		return (0);
	temp.x = sqrtf(discr);
	temp.z = (-temp.y - temp.x) / 2;
	temp.y = (-temp.y + temp.x) / 2;
	if (temp.y > temp.z)
		temp.y = temp.z;
	if ((temp.y > 0.001f) && (temp.y < *t))
		*t = temp.y;
	return ((*t == temp.y) ? 1 : 0);
}
