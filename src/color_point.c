/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 23:43:48 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/19 04:30:24 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	calc_blinn(t_recurse *rec)
{
	t_vec3		half;
	float		blinn_term;
	float		reflect;
	float		gloss;

	reflect = ((t_sphere *)rec->closest->content)->props.reflect;
	gloss = ((t_sphere *)rec->closest->content)->props.gloss;
	sub_vect(&rec->light_ray.dir, &rec->r.dir, &half);
	normalize_vector(&half);
	blinn_term = dot_vect(&half, &rec->n);
	blinn_term = MAX(0, reflect * powf(blinn_term, gloss * 100));
	if (gloss < 0.1)
		blinn_term = 0;
	return (blinn_term);
}

static float	calc_noise_coef(t_recurse *rec)
{
	float	noise_coef;
	int		level;

	noise_coef = 0.0;
	level = 0;
	while (++level < 10)
	{
		noise_coef += (1.0f / level)
		* fabs((float)noise(level * 0.05 * rec->r.start.x,
		level * 0.05 * rec->r.start.y,
		level * 0.05 * rec->r.start.z));
	}
	return (noise_coef);
}

void			color_point(t_recurse *rec)
{
	float	lambert;
	float	blinn;
	float	noise_coef;

	rec->lit = 1;
	lambert = dot_vect(&rec->light_ray.dir, &rec->n);
	if (((t_sphere *)rec->closest->content)->props.material == MAT_MARBLE)
	{
		noise_coef = calc_noise_coef(rec);
		lambert *= 1 - noise_coef / 4;
	}
	rec->light += lambert;
	blinn = calc_blinn(rec);
	lambert += blinn;
	lambert *= rec->coef;
	lambert *= rec->light_ray.radiance;
	lambert *= (1.0 - ((t_sphere *)rec->closest->content)->props.reflect);
	rec->color.r += lambert * rec->light_ray.color.r *
		((t_sphere *)rec->closest->content)->props.color.r;
	rec->color.g += lambert * rec->light_ray.color.g *
		((t_sphere *)rec->closest->content)->props.color.g;
	rec->color.b += lambert * rec->light_ray.color.b *
		((t_sphere *)rec->closest->content)->props.color.b;
}
