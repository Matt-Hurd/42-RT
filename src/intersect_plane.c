/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 20:57:34 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/31 22:44:54 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normal_plane(t_ray *r, t_plane *p, t_vec3 *n)
{
	*n = p->props.rot;
	if (dot_vect(&r->dir, &p->props.rot) > 0)
		scale_vector(-1, n, n);
	normalize_vector(n);
}

int		intersect_plane(t_ray *r, t_plane *p, float *t)
{
	float		n;
	float		d;
	float		res;
	t_vec3		temp;

	sub_vect(&p->props.pos, &r->start, &temp);
	n = dot_vect(&p->props.rot, &temp);
	d = dot_vect(&p->props.rot, &r->dir);
	if ((res = n / d) > 0.01 && res < *t)
		*t = res;
	return ((res == *t) ? 1 : 0);
}
