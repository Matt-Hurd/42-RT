/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_trans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 00:54:34 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/01 03:25:00 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		snells(t_data *d, t_recurse *recurse, float new_dens, float old_dens)
{
	float	cosi;
	float	sinsq;
	float	sint;
	t_vec3	temp[2];

	(void)d;
	// if (new_dens >= old_dens)
		scale_vector(-1, &recurse->n, &recurse->n);
	sint = dot_vect(&recurse->r.dir, &recurse->n) / (sqrtf(dot_vect(&recurse->r.dir, &recurse->r.dir) * sqrtf(dot_vect(&recurse->n, &recurse->n))));
	// if (sint > new_dens / old_dens)
	// 	return (0);
	cosi = dot_vect(&recurse->r.dir, &recurse->n);
	sinsq = powf((old_dens / new_dens), 2) * (1 - powf(cosi, 2));
	scale_vector(old_dens / new_dens, &recurse->r.dir, &temp[0]);
	scale_vector((old_dens / new_dens) * cosi - sqrtf(1 - sinsq), &recurse->n, &temp[1]);
	add_vect(&temp[0], &temp[1], &recurse->r.dir);
	normalize_vector(&recurse->r.dir);
	return (1);
}

float	handle_trans(t_data *d, t_recurse *rec)
{
	t_recurse	*recurse;
	float		t;
	t_vec3		temp;

	t = 10000000;
	recurse = (t_recurse *)ft_memalloc(sizeof(t_recurse));
	recurse->coef = ((t_sphere *)rec->closest->content)->props.trans;
	recurse->r = rec->r;
	recurse->n = rec->n;
	add_vect(&rec->r.start, &rec->r.dir, &recurse->r.start);
	recurse->depth = rec->depth;
	snells(d, recurse, ((t_sphere *)rec->closest->content)->props.density, 1);
	intersect_shape(&recurse->r, rec->closest, &t, 1);
	scale_vector(t, &recurse->r.dir, &temp);
	add_vect(&recurse->r.start, &temp, &recurse->r.start);
	normal_shape(&recurse->r, &recurse->n, rec->closest, 1);
	snells(d, recurse, 1, ((t_sphere *)rec->closest->content)->props.density);
	ray_trace(d, recurse);
	rec->color.r += recurse->color.r;
	rec->color.g += recurse->color.g;
	rec->color.b += recurse->color.b;
	free(recurse);
	return (1); //replace with Fresnel
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
