/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 17:29:15 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/16 21:15:05 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	regular_pixel(t_args *a, t_vec3 point, t_recurse *rec)
{
	t_ray		r;

	scale_vector(1, &a->d->s->cam_pos, &r.start);
	ft_vec_mult_mat(&point, a->global, &point);
	sub_vect(&point, &r.start, &r.dir);
	normalize_vector(&r.dir);
	rec->coef = 1.0;
	rec->r = r;
	rec->start = point;
	normalize_vector(&rec->start);
	rec->depth = 0;
	ray_trace(a->d, rec);
}

float	find_diff(t_args *a, t_rgb *avg)
{
	float	diff;
	int		x;
	int		y;

	y = -1;
	diff = 0;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			diff += fabs(a->colors[x].r - a->colors[y].r);
			diff += fabs(a->colors[x].g - a->colors[y].g);
			diff += fabs(a->colors[x].b - a->colors[y].r);
		}
		add_colors(avg, &a->colors[y], avg);
	}
	return (diff);
}

void	ssaa2(t_args *a, t_vec3 point, t_recurse *rec, int depth)
{
	int		x;
	int		y;
	float	diff;
	t_rgb	avg;
	t_vec3	new;

	y = -1;
	diff = 0;
	clear_color(&avg);
	diff = find_diff(a, &avg);
	if (depth < 1 && diff >= 1)
	{
		clear_color(&avg);
		x = -1;
		while (++x < 4)
		{
			new = point;
			new.x += 1.0 / pow(2, depth + 1) * ((x % 2) ? -1 : 1);
			new.y += 1.0 / pow(2, depth + 1) * ((x / 2) ? 1 : -1);
			ssaa(a, new, rec, depth + 1);
			add_colors(&avg, &rec->color, &avg);
		}
	}
	scale_color(0.25, &avg, &rec->color);
}

void	ssaa(t_args *a, t_vec3 point, t_recurse *rec, int depth)
{
	t_ray	r;
	t_vec3	new;
	int		x;

	x = -1;
	rec->start = point;
	normalize_vector(&rec->start);
	while (++x < 4)
	{
		clear_color(&rec->color);
		new = point;
		new.x += 1.0 / pow(2, depth) * ((x % 2) ? -1 : 1);
		new.y += 1.0 / pow(2, depth) * ((x / 2) ? 1 : -1);
		scale_vector(1, &a->d->s->cam_pos, &r.start);
		ft_vec_mult_mat(&new, a->global, &new);
		sub_vect(&new, &r.start, &r.dir);
		normalize_vector(&r.dir);
		rec->coef = 1.0;
		rec->r = r;
		rec->depth = 0;
		ray_trace(a->d, rec);
		a->colors[x] = rec->color;
	}
	ssaa2(a, point, rec, depth);
}
