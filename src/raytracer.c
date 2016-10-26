/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 22:42:52 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/22 22:48:02 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ray_trace(t_data *d, t_ray r, int depth)
{
	t_list	*curr;
	float	t;

	t = 30000;
	curr = d->scene->objects;
	d->scene->closest = NULL;
	while (curr)
	{
		if (intersect_shape(&r, curr->content, curr->content_size, &t))
			d->scene->closest = curr;
		curr = curr->next;
	}
	if (d->scene->closest)
	{
		find_light(d, t, curr, &r);
		if (depth < d->scene->maxdepth && d->scene->coef > 0)
		{
			ray_trace(d, r, depth + 1);
		}
	}
}

void	find_light(t_data *d, float t, t_list *curr, t_ray *r)
{
	t_vec3	n;
	t_vec3	*temp;

	temp = (t_vec3 *)ft_memalloc(sizeof(t_vec3));
	scale_vector(t, &r->dir, temp);
	ft_add_vector(&r->start, temp, &r->start);
	normal_shape(r, &n, d->scene->closest);
	curr = d->scene->objects;
	while (curr)
	{
		if (curr->content_size == LIGHT)
			calc_light(d, curr, r, n);
		curr = curr->next;
	}
	scale_vector(2 * dot_vect(&r->dir, &n), &n, temp);
	sub_vect(&r->dir, temp, &r->dir);
	free(temp);
	d->scene->coef *= ((t_sphere *)d->scene->closest->content)->props.reflect;
}

void	calc_light(t_data *d, t_list *curr, t_ray *r, t_vec3 n)
{
	int		obscured;
	t_vec3	dist;
	float	t;
	t_list	*curr2;

	obscured = 0;
	d->scene->current_light = *(t_light *)curr->content;
	sub_vect(&d->scene->current_light.props.pos, &r->start, &dist);
	t = sqrtf(dot_vect(&dist, &dist));
	if (!(dot_vect(&n, &dist) <= 0.0f || t <= 0.0))
	{
		d->scene->light_ray.start = r->start;
		normalize_vector(&dist);
		d->scene->light_ray.dir = dist;
		curr2 = d->scene->objects;
		while (curr2 && !obscured)
		{
			if (intersect_shape(&d->scene->light_ray,
				curr2->content, curr2->content_size, &t))
				obscured = 1;
			curr2 = curr2->next;
		}
		if (!obscured)
			color_point(d, n, &d->scene->color);
	}
}

void	color_point(t_data *d, t_vec3 n, t_rgb *color)
{
	float lambert;

	lambert = dot_vect(&d->scene->light_ray.dir, &n) * d->scene->coef;
	color->r += lambert * d->scene->current_light.props.color.r *
	((t_sphere *)d->scene->closest->content)->props.color.r *
	d->scene->current_light.props.radiance * (1.0 -
		((t_sphere *)d->scene->closest->content)->props.reflect);
	color->g += lambert * d->scene->current_light.props.color.g *
	((t_sphere *)d->scene->closest->content)->props.color.g *
	d->scene->current_light.props.radiance * (1.0 -
		((t_sphere *)d->scene->closest->content)->props.reflect);
	color->b += lambert * d->scene->current_light.props.color.b *
	((t_sphere *)d->scene->closest->content)->props.color.b *
	d->scene->current_light.props.radiance * (1.0 -
		((t_sphere *)d->scene->closest->content)->props.reflect);
	d->scene->coef = lambert;
}
