/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 21:14:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/27 23:52:51 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normal_cone(t_ray *r, t_cone *c, t_vec3 *n)
{
	t_vec3	v;
	t_vec3	project;

	sub_vect(&r->start, &c->props.pos, &v);
	scale_vector(dot_vect(&v, &c->props.rot), &c->props.rot, &project);
	sub_vect(&v, &project, n);
	normalize_vector(n);
}

int		intersect_cone(t_ray *r, t_cone *c, float *t)
{
	t_vec3	tmp;
	float	a[3];
	float	b[3];
	float	discr;

	sub_vect(&r->start, &c->props.pos, &tmp);
	a[0] = dot_vect(&r->dir, &r->dir) - ((1 + SQ(c->radius)) *
		dot_vect(&r->dir, &c->props.rot) * dot_vect(&r->dir, &c->props.rot));
	a[1] = 2 * (dot_vect(&r->dir, &tmp) - ((1 + SQ(c->radius)) *
		dot_vect(&r->dir, &c->props.rot) * dot_vect(&tmp, &c->props.rot)));
	a[2] = dot_vect(&tmp, &tmp) - ((1 + SQ(c->radius)) *
		dot_vect(&tmp, &c->props.rot) * dot_vect(&tmp, &c->props.rot));
	discr = a[1] * a[1] - 4 * a[0] * a[2];
	if (discr == 0)
		b[2] = (-a[1] + sqrtf(discr)) / (2 * a[0]);
	else if (discr > 0)
	{
		b[0] = (-a[1] + sqrtf(discr)) / (2 * a[0]);
		b[1] = (-a[1] - sqrtf(discr)) / (2 * a[0]);
		b[2] = (b[0] < b[1] ? b[0] : b[1]);
		b[2] = (b[2] < 0 ? b[1] : b[2]);
	}
	if (b[2] > 0.1 && *t > b[2])
		*t = b[2];
	return (*t == b[2]);
}
