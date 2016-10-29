/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_trans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 00:54:34 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/29 08:21:54 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	handle_trans(t_data *d, t_recurse *rec)
{
	t_recurse	*recurse;

	recurse = (t_recurse *)ft_memalloc(sizeof(t_recurse));
	recurse->coef = ((t_sphere *)rec->closest->content)->props.trans;
	recurse->r = rec->r;
	add_vect(&rec->r.start, &rec->r.dir, &recurse->r.start);
	recurse->depth = rec->depth;
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
