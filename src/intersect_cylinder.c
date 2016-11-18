/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 21:14:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/18 01:00:48 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normal_cylinder(t_ray *r, t_cylinder *cy, t_vec3 *n, char i)
{
	t_vec3	v;
	t_vec3	project;

	sub_vect(&r->start, &cy->props.pos, &v);
	scale_vector(dot_vect(&v, &cy->props.rot), &cy->props.rot, &project);
	sub_vect(&v, &project, n);
	if (i)
		scale_vector(-1, n, n);
	normalize_vector(n);
}

int		intersect_cylinder(t_ray *r, t_cylinder *cy, float *t, char i)
{
	t_vec3	oc;
	t_vec3	delta;
	t_vec3	temp;
	float	a[3];
	float	discr;

	scale_vector(dot_vect(&r->dir, &cy->props.rot), &cy->props.rot, &oc);
	sub_vect(&r->dir, &oc, &oc);
	sub_vect(&r->start, &cy->props.pos, &delta);
	scale_vector(dot_vect(&delta, &cy->props.rot), &cy->props.rot, &temp);
	sub_vect(&delta, &temp, &delta);
	a[1] = 2 * dot_vect(&oc, &delta);
	a[2] = dot_vect(&delta, &delta) - SQ(cy->radius);
	discr = a[1] * a[1] - 4 * dot_vect(&oc, &oc) * a[2];
	a[0] = (-a[1] + sqrtf(discr)) / (2 * dot_vect(&oc, &oc));
	if (discr > 0)
	{
		a[2] = (-a[1] + sqrtf(discr)) / (2 * dot_vect(&oc, &oc));
		a[1] = (-a[1] - sqrtf(discr)) / (2 * dot_vect(&oc, &oc));
		a[0] = ((MIN(a[2], a[1]) < 0) ^ i ? MAX(a[2], a[1]) : MIN(a[2], a[1]));
	}
	if (discr >= 0 && a[0] > 0.1 && *t > a[0])
		*t = a[0];
	return (*t == a[0]);
}
