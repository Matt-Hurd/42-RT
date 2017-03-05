/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:35:53 by mhurd             #+#    #+#             */
/*   Updated: 2017/02/20 22:17:53 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_vec3(t_vec3 v, float scale)
{
	ft_putstr("(x: ");
	ft_putnbr(v.x * scale);
	ft_putstr(", y: ");
	ft_putnbr(v.y * scale);
	ft_putstr(", z: ");
	ft_putnbr(v.z * scale);
	ft_putendl(")");
}

void	print_rgb(t_rgb rgb)
{
	ft_putstr("(r: ");
	ft_putnbr(rgb.r * 255);
	ft_putstr(", g: ");
	ft_putnbr(rgb.g * 255);
	ft_putstr(", b: ");
	ft_putnbr(rgb.b * 255);
	ft_putendl(")");
}

void	print_properties(t_props p)
{
	ft_putstr("	Pos: ");
	print_vec3(p.pos, 1);
	ft_putstr("	Rot: ");
	print_vec3(p.rot, (180.0 / M_PI));
	ft_putstr("	Color: ");
	print_rgb(p.color);
	ft_putstr("	Reflectivity:");
	ft_putnbr(p.reflect * 100);
	ft_putstr("\n	Radiance:");
	ft_putnbr(p.radiance * 100);
	ft_putstr("\n	Translucency:");
	ft_putnbr(p.trans * 100);
	ft_putstr("\n	Density:");
	ft_putnbr(p.density * 100);
	ft_putchar('\n');
}

void	print_scene(t_data *d)
{
	ft_putstr("[Scene]\n");
	ft_putstr("	Ambient Light: ");
	ft_putnbr(d->s->ambient * 100);
	ft_putstr("\n	Anti-Aliasing: ");
	ft_putnbr(d->s->aa);
	ft_putstr("\n");
}

void	print_scene_info(t_data *d)
{
	int		x;
	t_list	*a;

	x = 0;
	a = d->s->objects;
	print_scene(d);
	while (a)
	{
		ft_putnbr(++x);
		ft_putstr(") ");
		if (a->content_size == SPHERE)
			print_sphere_info(a->content);
		if (a->content_size == CONE)
			print_cone_info(a->content);
		if (a->content_size == CYLINDER)
			print_cylinder_info(a->content);
		if (a->content_size == PLANE)
			print_plane_info(a->content);
		if (a->content_size == LIGHT)
			print_light_info(a->content);
		if (a->content_size == MODEL)
			print_model_info(a->content);
		ft_putendl("");
		a = a->next;
	}
}
