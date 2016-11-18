/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_trans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 00:54:34 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/16 20:17:56 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	snells(t_recurse *recurse, float new_dens, float old_dens)
{
	float	temp;
	float	schlick;
	t_vec3	tmp[2];

	scale_vector(dot_vect(&recurse->r.dir, &recurse->n), &recurse->n, &tmp[0]);
	sub_vect(&recurse->r.dir, &tmp[0], &tmp[0]);
	scale_vector(old_dens / new_dens, &tmp[0], &tmp[0]);
	temp = 1 - (powf(old_dens, 2) / powf(new_dens, 2)) *
		(1 - powf(dot_vect(&recurse->r.dir, &recurse->n), 2));
	if (temp < 0)
		return (-1);
	scale_vector(sqrtf(temp), &recurse->n, &tmp[1]);
	schlick = powf((new_dens - 1) / (new_dens + 1), 2);
	if (old_dens <= new_dens)
		schlick +=
			(1 - schlick) * powf(1 + dot_vect(&recurse->r.dir, &recurse->n), 5);
	sub_vect(&tmp[0], &tmp[1], &recurse->r.dir);
	normalize_vector(&recurse->r.dir);
	if (old_dens > new_dens)
		schlick +=
			(1 - schlick) * powf(1 + dot_vect(&recurse->r.dir, &recurse->n), 5);
	return (schlick);
}

float	find_inter(t_data *d, t_recurse *rec, t_recurse *recurse, float t[3])
{
	t_list		*tmp;

	tmp = d->s->objects;
	while (tmp)
	{
		t[1] = t[0];
		intersect_shape(&recurse->r, tmp, &t[1], 1);
		tmp = tmp->next;
		if (t[1] != t[0])
		{
			ray_trace(d, recurse);
			add_colors(&rec->color, &recurse->color, &rec->color);
			free(recurse);
			t[2] = (1.0 - ((t_sphere *)rec->closest->content)->props.trans);
			return (t[2]);
		}
	}
	t[2] = -1;
	return (t[2]);
}

void	clone_recurse(t_recurse *new, t_recurse *old)
{
	new->r = old->r;
	new->n = old->n;
	new->depth = old->depth;
}

float	handle_trans(t_data *d, t_recurse *rec)
{
	t_recurse	*recurse;
	float		t[3];
	t_vec3		temp;

	if (rec->closest->content_size != SPHERE)
		return (1);
	t[0] = 10000000;
	recurse = (t_recurse *)ft_memalloc(sizeof(t_recurse));
	clone_recurse(recurse, rec);
	t[1] = snells(recurse, ((t_cone *)rec->closest->content)->props.density, 1);
	if (t[1] == -1)
		return (1);
	recurse->coef =
		(1.0 - t[1]) * ((t_sphere *)rec->closest->content)->props.trans;
	intersect_shape(&recurse->r, rec->closest, &t[0], 1);
	if (find_inter(d, rec, recurse, t) != -1)
		return (t[2]);
	scale_vector(t[0], &recurse->r.dir, &temp);
	add_vect(&recurse->r.start, &temp, &recurse->r.start);
	normal_shape(&recurse->r, &recurse->n, rec->closest, 1);
	snells(recurse, 1, ((t_sphere *)rec->closest->content)->props.density);
	ray_trace(d, recurse);
	add_colors(&rec->color, &recurse->color, &rec->color);
	free(recurse);
	return (1.0 - ((t_sphere *)rec->closest->content)->props.trans);
}

void	pass_through(t_data *d, t_recurse *rec, float *obscured, t_list *curr2)
{
	t_rgb		new;
	t_rgb		diff;
	float		t;
	float		i;
	t_list		*tmp;

	t = 10000;
	*obscured -= (1.0 - ((t_sphere *)curr2->content)->props.trans);
	tmp = d->s->objects;
	while (tmp)
	{
		intersect_shape(&rec->light_ray, tmp, &t, 1);
		tmp = tmp->next;
	}
	i = powf(M_E,
		-log(2) * t / 120);
	rec->light_ray.radiance *=
		(1 - i) * ((t_sphere *)curr2->content)->props.trans;
	sub_colors(&rec->light_ray.color,
		&((t_sphere *)curr2->content)->props.color, &diff);
	scale_color(i, &diff, &diff);
	sub_colors(&rec->light_ray.color, &diff, &new);
	rec->light_ray.color.r = MAX(MIN(rec->light_ray.color.r, new.r), 0);
	rec->light_ray.color.g = MAX(MIN(rec->light_ray.color.g, new.g), 0);
	rec->light_ray.color.b = MAX(MIN(rec->light_ray.color.b, new.b), 0);
}
