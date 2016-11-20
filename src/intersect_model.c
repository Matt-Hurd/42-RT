/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_model.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 06:50:05 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/19 07:42:30 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normal_model(t_ray *r, t_model *m, t_vec3 *n, char intern)
{
	n->x = m->normals[r->face].x;
	n->y = m->normals[r->face].y;
	n->z = m->normals[r->face].z;
	if (intern)
		scale_vector(1, n, n);
	normalize_vector(n);
}

int		intersect_triangle(t_ray *r, t_vec3 vertices[3], float *t)
{
	t_vec3	tmp_vecs[5];
	float	tmp_floats[4];

	sub_vect(&vertices[1], &vertices[0], &tmp_vecs[0]);
	sub_vect(&vertices[2], &vertices[0], &tmp_vecs[1]);
	cross_vect(&r->dir, &tmp_vecs[1], &tmp_vecs[2]);
	tmp_floats[0] = dot_vect(&tmp_vecs[0], &tmp_vecs[2]);
	if (tmp_floats[0] > -0.001 && tmp_floats[0] < 0.001)
		return (0);
	tmp_floats[1] = 1 / tmp_floats[0];
	sub_vect(&r->start, &vertices[0], &tmp_vecs[3]);
	tmp_floats[2] = tmp_floats[1] * (dot_vect(&tmp_vecs[3], &tmp_vecs[2]));
	if (tmp_floats[2] < 0.0 || tmp_floats[2] > 1.0)
		return (0);
	cross_vect(&tmp_vecs[3], &tmp_vecs[0], &tmp_vecs[4]);
	tmp_floats[3] = tmp_floats[1] * dot_vect(&r->dir, &tmp_vecs[4]);
	if (tmp_floats[3] < 0.0 || tmp_floats[2] + tmp_floats[3] > 1.0)
		return (0);
	*t = tmp_floats[1] * dot_vect(&tmp_vecs[1], &tmp_vecs[4]);
	return (*t > 0.001 ? 1 : 0);
}

int		intersect_model(t_ray *r, t_model *m, float *t)
{
	t_vec3		vertices[3];
	int			x;
	float		new;
	float		min;
	int			face;

	x = -1;
	min = *t;
	face = 0;
	while (++x < m->face_count)
	{
		new = *t;
		vertices[0] = m->vertices[m->faces[x][0] - 1];
		vertices[1] = m->vertices[m->faces[x][1] - 1];
		vertices[2] = m->vertices[m->faces[x][2] - 1];
		if (intersect_triangle(r, vertices, &new) && new < min && (min = new))
			face = m->faces[x][3] - 1;
	}
	if (min != *t)
	{
		*t = min;
		r->face = face;
		return (1);
	}
	return (0);
}
