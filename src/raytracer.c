/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 22:42:52 by mhurd             #+#    #+#             */
/*   Updated: 2017/03/04 23:09:04 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ray_trace(t_data *d, t_recurse *rec)
{
	t_list	*curr;
	float	t;

	t = 3000000;
	curr = d->s->objects;
	rec->closest = NULL;
	while (curr)
	{
		if (intersect_shape(&rec->r, curr, &t, 0))
			rec->closest = curr;
		curr = curr->next;
	}
	if (rec->closest)
	{
		rec->lit = d->s->ambient;
		color_ambient(d->s->ambient, rec);
		find_light(d, t, rec);
		if (rec->depth++ < d->s->maxdepth && rec->coef > 0 && rec->lit)
			ray_trace(d, rec);
	}
}

void	bump_map(t_vec3 *n, t_props props, t_vec3 hit, t_recurse *rec)
{
	float noise_x;
	float noise_y;
	float noise_z;

	if (props.bump > 0)
	{
		if (props.material != MAT_RIPPLE)
		{
			noise_x = noise(0.1 * hit.x,
				0.1 * hit.y, 0.1 * hit.z);
			noise_y = noise(0.1 * hit.y,
				0.1 * hit.z, 0.1 * hit.x);
			noise_z = noise(0.1 * hit.z,
				0.1 * hit.x, 0.1 * hit.y);
			n->y = (1.0f - props.bump)
				* n->y + props.bump * noise_y;
			n->z = (1.0f - props.bump)
				* n->z + props.bump * noise_z;
		}
		else
			noise_x = handle_mats(rec);
		n->x = (1.0f - props.bump)
			* n->x + props.bump * noise_x;
		normalize_vector(n);
	}
}

void	find_light(t_data *d, float t, t_recurse *rec)
{
	t_vec3	*temp;
	t_list	*curr;

	temp = (t_vec3 *)ft_memalloc(sizeof(t_vec3));
	scale_vector(t, &rec->r.dir, temp);
	add_vect(&rec->r.start, temp, &rec->r.start);
	normal_shape(&rec->r, &rec->n, rec->closest, 0);
	curr = d->s->objects;
	rec->light = 0;
	bump_map(&rec->n, ((t_sphere *)rec->closest->content)->props, rec->r.start,
		rec);
	if (((t_sphere *)rec->closest->content)->props.trans > 0)
		rec->coef *= handle_trans(d, rec);
	while (curr)
	{
		if (curr->content_size == LIGHT)
			calc_light(d, rec, curr);
		curr = curr->next;
	}
	scale_vector(2 * dot_vect(&rec->r.dir, &rec->n), &rec->n, temp);
	sub_vect(&rec->r.dir, temp, &rec->r.dir);
	free(temp);
	rec->coef *= ((t_sphere *)rec->closest->content)->props.reflect;
	rec->coef *= MIN(rec->light, 1);
}

void	calc_light(t_data *d, t_recurse *rec, t_list *curr)
{
	float	obscured;
	float	t[2];
	t_list	*curr2;

	obscured = 1.0;
	rec->current_light = *(t_light *)curr->content;
	sub_vect(&rec->current_light.props.pos, &rec->r.start, &rec->light_ray.dir);
	t[0] = sqrtf(dot_vect(&rec->light_ray.dir, &rec->light_ray.dir));
	if (!(dot_vect(&rec->n, &rec->light_ray.dir) <= 0.0f || t[0] <= 0.0))
	{
		rec->light_ray.start = rec->r.start;
		normalize_vector(&rec->light_ray.dir);
		rec->light_ray.color = rec->current_light.props.color;
		rec->light_ray.radiance = rec->current_light.props.radiance;
		curr2 = d->s->objects;
		while ((t[1] = t[0]) && curr2 && obscured > 0.0)
		{
			if (intersect_shape(&rec->light_ray, curr2, &t[1], 0) ||
				intersect_shape(&rec->light_ray, curr2, &t[1], 1))
				pass_through(d, rec, &obscured, curr2);
			curr2 = curr2->next;
		}
		if (obscured > 0.0)
			color_point(rec);
	}
}
