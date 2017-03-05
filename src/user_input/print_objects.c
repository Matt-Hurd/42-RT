/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:35:41 by mhurd             #+#    #+#             */
/*   Updated: 2017/02/20 22:17:10 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_sphere_info(t_sphere *sphere)
{
	ft_putendl("[sphere]");
	ft_putstr("	Radius: ");
	ft_putnbr(sphere->radius);
	ft_putendl("");
	print_properties(sphere->props);
}

void	print_plane_info(t_plane *plane)
{
	ft_putendl("[plane]");
	print_properties(plane->props);
}

void	print_cone_info(t_cone *cone)
{
	ft_putendl("[cone]");
	ft_putstr("	Radius: ");
	ft_putnbr(cone->radius);
	ft_putendl("");
	print_properties(cone->props);
}

void	print_cylinder_info(t_cylinder *cylinder)
{
	ft_putendl("[cylinder]");
	ft_putstr("	Radius: ");
	ft_putnbr(cylinder->radius);
	ft_putendl("");
	print_properties(cylinder->props);
}

void	print_light_info(t_light *light)
{
	ft_putendl("[light]");
	print_properties(light->props);
}
