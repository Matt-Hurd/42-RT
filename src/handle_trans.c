/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_trans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 00:54:34 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/02 05:46:41 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>

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
		schlick += (1 - schlick) * powf(1 - dot_vect(&recurse->r.dir, &recurse->n), 5);
	sub_vect(&tmp[0], &tmp[1], &recurse->r.dir);
	normalize_vector(&recurse->r.dir);
	if (old_dens > new_dens)
		schlick += (1 - schlick) * powf(1 - dot_vect(&recurse->r.dir, &recurse->n), 5);
	return (schlick);
}

float	handle_trans(t_data *d, t_recurse *rec)
{
	t_recurse	*recurse;
	float		t[2];
	t_vec3		temp;

	t[0] = 10000000;
	recurse = (t_recurse *)ft_memalloc(sizeof(t_recurse));
	recurse->r = rec->r;
	recurse->n = rec->n;
	add_vect(&rec->r.start, &rec->r.dir, &recurse->r.start);
	recurse->depth = rec->depth;
	t[1] = snells(recurse, ((t_cone *)rec->closest->content)->props.density, 1);
	if (t[1] == -1)
		return (1);
	recurse->coef = ((t_sphere *)rec->closest->content)->props.trans;
	intersect_shape(&recurse->r, rec->closest, &t[0], 1);
	scale_vector(t[0], &recurse->r.dir, &temp);
	add_vect(&recurse->r.start, &temp, &recurse->r.start);
	normal_shape(&recurse->r, &recurse->n, rec->closest, 1);
	snells(recurse, 1, ((t_sphere *)rec->closest->content)->props.density);
	ray_trace(d, recurse);
	add_colors(&rec->color, &recurse->color, &rec->color);
	free(recurse);
	// printf("%f\n", t[1]);
	return (t[1] * (1.0 - ((t_sphere *)rec->closest->content)->props.trans));
}

void	pass_through(t_data *d, t_recurse *rec, float *obscured, t_list *curr2)
{
	t_rgb new;

	(void)d;
	new = rec->light_ray.color;
	*obscured -= (1.0 - ((t_sphere *)curr2->content)->props.trans);
	new.r -= ((t_sphere *)curr2->content)->props.color.r;
	new.g -= ((t_sphere *)curr2->content)->props.color.g;
	new.b -= ((t_sphere *)curr2->content)->props.color.b;
	rec->light_ray.color.r = MIN(rec->light_ray.color.r, new.r);
	rec->light_ray.color.g = MIN(rec->light_ray.color.g, new.g);
	rec->light_ray.color.b = MIN(rec->light_ray.color.b, new.b);
}
