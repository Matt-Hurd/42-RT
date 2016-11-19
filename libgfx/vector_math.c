/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 20:34:51 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/18 08:56:34 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

void	scale_vector(float c, t_vec3 *v, t_vec3 *d)
{
	d->x = v->x * c;
	d->y = v->y * c;
	d->z = v->z * c;
}

void	normalize_vector(t_vec3 *v)
{
	float div;

	div = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= div;
	v->y /= div;
	v->z /= div;
}

void	cross_vect(t_vec3 *v1, t_vec3 *v2, t_vec3 *out)
{
	out->x = v1->y * v2->z - v1->z * v2->y;
	out->y = v1->z * v2->x - v1->x * v2->z;
	out->z = v1->x * v2->y - v1->y * v2->x;
}

float	length_vect(t_vec3 *in)
{
	return (sqrtf(pow(in->x, 2) + pow(in->y, 2) + pow(in->z, 2)));
}

float	dot_vect(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

void	add_vect(t_vec3 *v1, t_vec3 *v2, t_vec3 *d)
{
	d->x = v1->x + v2->x;
	d->y = v1->y + v2->y;
	d->z = v1->z + v2->z;
}

void	sub_vect(t_vec3 *v1, t_vec3 *v2, t_vec3 *d)
{
	d->x = v1->x - v2->x;
	d->y = v1->y - v2->y;
	d->z = v1->z - v2->z;
}
