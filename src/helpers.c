/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 20:32:43 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/27 23:03:23 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_color(char *color, t_rgb *ref)
{
	char **buff;

	buff = ft_strsplit(color, ',');
	if (ft_count_words(color, ',') != 3)
		ft_error("Config Format Error");
	ref->r = (float)ft_atoi(buff[0]) / 255;
	ref->g = (float)ft_atoi(buff[1]) / 255;
	ref->b = (float)ft_atoi(buff[2]) / 255;
}

void	clear_color(t_rgb *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void	normal_shape(t_ray *r, t_vec3 *n, t_list *s)
{
	if (s->content_size == SPHERE)
		normal_sphere(r, s->content, n);
	else if (s->content_size == CYLINDER)
		normal_cylinder(r, s->content, n);
	else if (s->content_size == PLANE)
		normal_plane(r, s->content, n);
	else if (s->content_size == CONE)
		normal_cone(r, s->content, n);
	else
		return ;
}

int		intersect_shape(t_ray *r, void *s, int type, float *t)
{
	if (type == SPHERE)
		return (intersect_sphere(r, s, t));
	if (type == CYLINDER)
		return (intersect_cylinder(r, s, t));
	if (type == PLANE)
		return (intersect_plane(r, s, t));
	if (type == CONE)
		return (intersect_cone(r, s, t));
	else
		return (0);
}
